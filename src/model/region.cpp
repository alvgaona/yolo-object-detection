#include "model/region.h"

Region::Region(float threshold) : threshold_(threshold) {}

void Region::ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs, std::vector<cv::Rect>& boxes,
                          std::vector<float> &confidences, std::vector<int>& class_ids) {
  for (const auto& prediction_output : prediction_outputs) {
    // Network produces output blob with a shape NxC where N is a number of
    // detected objects and C is a number of classes + 4 where the first 4
    // numbers are [center_x, center_y, width, height]
    auto data = (float*)prediction_output.data;
    for (int j = 0; j < (prediction_output.rows); ++j, data += (prediction_output.cols)) {
      cv::Mat scores = (prediction_output.row(j).colRange(5, (prediction_output.cols)));
      cv::Point classIdPoint;
      double confidence;
      cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
      if (confidence > threshold_) {
        int centerX = static_cast<int>(data[0] * frame.cols);
        int centerY = static_cast<int>(data[1] * frame.rows);
        int width = static_cast<int>(data[2] * frame.cols);
        int height = static_cast<int>(data[3] * frame.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        class_ids.push_back(classIdPoint.x);
        confidences.push_back((float)confidence);
        boxes.emplace_back(cv::Rect(left, top, width, height));
      }
    }
  }
}
