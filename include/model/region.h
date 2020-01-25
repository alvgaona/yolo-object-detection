#ifndef YOLO_OBJECT_DETECTION_REGION_H
#define YOLO_OBJECT_DETECTION_REGION_H

#include "configuration.h"
#include "model/output_layer.h"

class Region : public OutputLayer {
 public:
  Region() = default;
  virtual ~Region() override = default;

  void ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs, std::vector<cv::Rect>& boxes,
                            std::vector<float> &confidences, std::vector<int>& class_ids) override;
};

#endif
