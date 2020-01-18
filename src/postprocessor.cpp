#include "postprocessor.h"

Postprocessor::Postprocessor(Postprocessor&& source) noexcept {}

void Postprocessor::process(cv::Mat& frame, cv::dnn::Net& net, const std::vector<cv::Mat>& prediction_outputs,
                            const std::vector<std::string>& classes) {
  static std::vector<int> outLayers = net.getUnconnectedOutLayers();
  static std::string outLayerType = net.getLayer(outLayers[0])->type;

  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;
  if (outLayerType == "DetectionOutput") {
    // Network produces output blob with a shape 1x1xNx7 where N is a number of
    // detections and an every detection is a vector of values
    // [batchId, classId, confidence, left, top, right, bottom]
    CV_Assert(!prediction_outputs.empty());
    for (const auto &prediction_output : prediction_outputs) {
      auto data = (float*)prediction_output.data;
      for (size_t i = 0; i < prediction_output.total(); i += 7) {
        float confidence = data[i + 2];
        if (confidence > Configuration::THRESHOLD) {
          int left = static_cast<int>(data[i + 3]);
          int top = static_cast<int>(data[i + 4]);
          int right = static_cast<int>(data[i + 5]);
          int bottom = static_cast<int>(data[i + 6]);
          int width = right - left + 1;
          int height = bottom - top + 1;
          if (width <= 2 || height <= 2) {
            left = static_cast<int>(data[i + 3] * frame.cols);
            top = static_cast<int>(data[i + 4] * frame.rows);
            right = static_cast<int>(data[i + 5] * frame.cols);
            bottom = static_cast<int>(data[i + 6] * frame.rows);
            width = right - left + 1;
            height = bottom - top + 1;
          }
          classIds.push_back(static_cast<int>(data[i + 1]) - 1);  // Skip 0th background class id.
          boxes.emplace_back(cv::Rect(left, top, width, height));
          confidences.push_back(confidence);
        }
      }
    }
  } else if (outLayerType == "Region") {
    for (const auto &prediction_output : prediction_outputs) {
      // Network produces output blob with a shape NxC where N is a number of
      // detected objects and C is a number of classes + 4 where the first 4
      // numbers are [center_x, center_y, width, height]
      auto data = (float*)prediction_output.data;
      for (int j = 0; j < (prediction_output.rows); ++j, data += (prediction_output.cols)) {
        cv::Mat scores = (prediction_output.row(j).colRange(5, (prediction_output.cols)));
        cv::Point classIdPoint;
        double confidence;
        minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
        if (confidence > Configuration::THRESHOLD) {
          int centerX = static_cast<int>(data[0] * frame.cols);
          int centerY = static_cast<int>(data[1] * frame.rows);
          int width = static_cast<int>(data[2] * frame.cols);
          int height = static_cast<int>(data[3] * frame.rows);
          int left = centerX - width / 2;
          int top = centerY - height / 2;

          classIds.push_back(classIdPoint.x);
          confidences.push_back((float)confidence);
          boxes.emplace_back(cv::Rect(left, top, width, height));
        }
      }
    }
  } else {
    CV_Error(cv::Error::StsNotImplemented, "Unknown output layer type: " + outLayerType);
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, Configuration::THRESHOLD, Configuration::NMS_THRESHOLD, indices);
  for (auto &idx : indices) {
    cv::Rect box = boxes[idx];
    drawPred(classes, classIds[idx], confidences[idx], box.x, box.y, box.x + box.width,
             box.y + box.height, frame);
  }
}

void Postprocessor::drawPred(const std::vector<std::string>& classes, int classId, float conf, int left, int top, int right,
                             int bottom, cv::Mat& frame) {
  rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 255, 0));

  std::string label = cv::format("%.2f", conf);
  if (!classes.empty()) {
    CV_Assert(classId < static_cast<int>(classes.size()));
    label = classes[classId] + ": " + label;
  }

  int baseLine;
  cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

  top = cv::max(top, labelSize.height);
  rectangle(frame, cv::Point(left, top - labelSize.height), cv::Point(left + labelSize.width, top + baseLine),
            cv::Scalar::all(255), cv::FILLED);
  putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar());
}
