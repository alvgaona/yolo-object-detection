#ifndef YOLO_OBJECT_DETECTION_PREPROCESSOR_H
#define YOLO_OBJECT_DETECTION_PREPROCESSOR_H

#include <opencv2/opencv.hpp>

#include "configuration.h"

class Preprocessor {
 public:
  Preprocessor() = default;
  ~Preprocessor() = default;
  Preprocessor(const Preprocessor& source) = delete;
  Preprocessor(Preprocessor&& source) noexcept;

  Preprocessor& operator=(const Preprocessor& source) = delete;
  Preprocessor& operator=(Preprocessor&& source) noexcept = delete;

  void process(cv::Mat& frame, cv::dnn::Net& net, struct Configuration::FrameProcessingData& data);
};

#endif
