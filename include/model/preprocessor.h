#ifndef YOLO_OBJECT_DETECTION_PREPROCESSOR_H
#define YOLO_OBJECT_DETECTION_PREPROCESSOR_H

#include <opencv2/opencv.hpp>

#include "utils/yolo_utils.h"

class Preprocessor {
 public:
  Preprocessor() = default;
  ~Preprocessor() = default;
  Preprocessor(const Preprocessor& source) = delete;
  Preprocessor(Preprocessor&& source) noexcept;

  Preprocessor& operator=(const Preprocessor& source) = delete;
  Preprocessor& operator=(Preprocessor&& source) noexcept = delete;

  void Process(cv::Mat& frame, cv::dnn::Net& net, struct YoloUtils::FrameProcessingData& data);
};

#endif
