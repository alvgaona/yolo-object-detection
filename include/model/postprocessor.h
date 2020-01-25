#ifndef YOLO_OBJECT_DETECTION_POSTPROCESSOR_H
#define YOLO_OBJECT_DETECTION_POSTPROCESSOR_H

#include <memory>

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include "configuration.h"
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

  void process(cv::Mat& frame, cv::dnn::Net& net, const std::vector<cv::Mat>& prediction_outputs,
               const std::vector<std::string>& classes);

 private:
  void drawPred(const std::vector<std::string>& classes, int classId, float conf, int left, int top, int right,
                int bottom, cv::Mat& frame);
};

#endif