#ifndef YOLO_OBJECT_DETECTION_REGION_H
#define YOLO_OBJECT_DETECTION_REGION_H

#include "model/output_layer.h"
#include "utils/yolo_utils.h"

class Region : public OutputLayer {
 public:
  Region() = default;
  Region(float threshold);
  virtual ~Region() override = default;

  Region(const Region& source) = delete;
  Region(Region&& source) noexcept = delete;

  Region& operator=(const Region& source) = delete;
  Region& operator=(Region&& source) noexcept = delete;

  void ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs, std::vector<cv::Rect>& boxes,
                    std::vector<float>& confidences, std::vector<int>& class_ids) override;

 private:
  float threshold_;
};

#endif
