#ifndef YOLO_OBJECT_DETECTION_POSTPROCESSOR_H
#define YOLO_OBJECT_DETECTION_POSTPROCESSOR_H

#include <memory>

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include "utils/yolo_utils.h"
#include "output_layers.h"
#include "output_layer.h"

class Postprocessor {
 public:
  Postprocessor() = default;
  ~Postprocessor() = default;
  Postprocessor(const Postprocessor& source) = delete;
  Postprocessor(Postprocessor&& source) noexcept;

  Postprocessor& operator=(const Postprocessor& source) = delete;
  Postprocessor& operator=(Postprocessor&& source) noexcept = delete;

  void Process(cv::Mat& frame, cv::dnn::Net& net, const std::vector<cv::Mat>& prediction_outputs,
               const std::vector<std::string>& classes, float threshold, float nms_threshold);

 private:
  void DrawPrediction(const std::vector<std::string>& classes, int classId, float conf, int left, int top, int right,
                int bottom, cv::Mat& frame);
};

#endif
