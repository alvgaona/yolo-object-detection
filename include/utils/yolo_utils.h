#ifndef YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H
#define YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H

#include <opencv2/core.hpp>

#include <string>

namespace YoloUtils {
struct FrameProcessingData {
  cv::Scalar mean;
  cv::Size input_size;
  bool rgb;
  float scale;
  float threshold;
  float nms_threshold;
};
}  // namespace YoloUtils

#endif
