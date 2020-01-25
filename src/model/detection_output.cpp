#include "model/detection_output.h"

DetectionOutput::DetectionOutput(float threshold) : threshold_(threshold) {}

void DetectionOutput::ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs,
                                   std::vector<cv::Rect>& boxes, std::vector<float> &confidences,
                                   std::vector<int>& class_ids) {
  CV_Assert(!prediction_outputs.empty());
  for (const auto& prediction_output : prediction_outputs) {
    auto data = (float*)prediction_output.data;
    for (size_t i = 0; i < prediction_output.total(); i += 7) {
      float confidence = data[i + 2];
      if (confidence > threshold_) {
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
        class_ids.push_back(static_cast<int>(data[i + 1]) - 1);  // Skip 0th background class id.
        boxes.emplace_back(cv::Rect(left, top, width, height));
        confidences.push_back(confidence);
      }
    }
  }
}
