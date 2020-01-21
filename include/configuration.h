#ifndef YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H
#define YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H

#include <opencv2/core.hpp>

#include <string>

// TODO: Read configuration from a YAML file.
namespace Configuration {
static constexpr float THRESHOLD = 0.5;
static constexpr float NMS_THRESHOLD = 0.4;
static constexpr int WIDTH = 416;
static constexpr int HEIGHT = 416;
static constexpr float SCALE = 0.00392;
static constexpr bool RGB = true;

struct FrameProcessingData {
  cv::Scalar mean;
  cv::Size input_size;
  bool rgb;
  float scale;
};
}  // namespace Configuration

#endif
