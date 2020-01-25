#ifndef YOLO_OBJECT_DETECTION_DETECTION_OUTPUT_H
#define YOLO_OBJECT_DETECTION_DETECTION_OUTPUT_H

#include "output_layer.h"
#include "utils/yolo_utils.h"

class DetectionOutput : public OutputLayer {
 public:
  DetectionOutput() = default;
  DetectionOutput(float threshold);
  virtual ~DetectionOutput() override = default;

  DetectionOutput(const DetectionOutput& source) = delete;
  DetectionOutput(DetectionOutput&& source) noexcept = delete;

  DetectionOutput& operator=(const DetectionOutput& source) = delete;
  DetectionOutput& operator=(DetectionOutput&& source) noexcept = delete;

  void ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs, std::vector<cv::Rect>& boxes,
                    std::vector<float>& confidences, std::vector<int>& class_ids) override;

 private:
  float threshold_;
};

#endif
