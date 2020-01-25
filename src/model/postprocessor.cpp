#include "model/postprocessor.h"

Postprocessor::Postprocessor(Postprocessor&& source) noexcept {}

void Postprocessor::Process(cv::Mat& frame, cv::dnn::Net& net, const std::vector<cv::Mat>& prediction_outputs,
                            const std::vector<std::string>& classes,
                            float threshold, float nms_threshold) {
  static std::vector<int> outLayers = net.getUnconnectedOutLayers();
  static std::string outLayerType = net.getLayer(outLayers[0])->type;

  std::vector<int> class_ids;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;

  std::unique_ptr<OutputLayer> output_layer = OutputLayers::of(outLayerType, threshold);

  output_layer->ComputeBoxes(frame, prediction_outputs, boxes, confidences, class_ids);

  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, threshold, nms_threshold, indices);
  for (auto &idx : indices) {
    cv::Rect box = boxes[idx];
    DrawPrediction(classes, class_ids[idx], confidences[idx], box.x, box.y, box.x + box.width,
             box.y + box.height, frame);
  }
}

void Postprocessor::DrawPrediction(const std::vector<std::string>& classes, int classId, float conf, int left, int top, int right,
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
