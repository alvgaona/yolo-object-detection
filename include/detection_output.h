#ifndef YOLO_OBJECT_DETECTION_DETECTION_OUTPUT_H
#define YOLO_OBJECT_DETECTION_DETECTION_OUTPUT_H

#include "configuration.h"
#include "output_layer.h"

class DetectionOutput : public OutputLayer {
 public:
  DetectionOutput() = default;
  virtual ~DetectionOutput() override = default;

  void ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs, std::vector<cv::Rect>& boxes,
                    std::vector<float> &confidences, std::vector<int>& class_ids) override;
};

#endif
