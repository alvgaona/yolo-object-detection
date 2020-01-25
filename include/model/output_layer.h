#ifndef YOLO_OBJECT_DETECTION_OUTPUT_LAYER_H
#define YOLO_OBJECT_DETECTION_OUTPUT_LAYER_H

#include <vector>

#include <opencv2/core.hpp>

class OutputLayer {
 public:
  OutputLayer() = default;
  virtual ~OutputLayer() = default;

  virtual void ComputeBoxes(cv::Mat& frame, const std::vector<cv::Mat>& prediction_outputs,
                            std::vector<cv::Rect>& boxes, std::vector<float>& confidences,
                            std::vector<int>& class_ids) = 0;
};

#endif
