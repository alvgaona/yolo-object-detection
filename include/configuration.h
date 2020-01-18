#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <opencv2/core.hpp>

#include <string>


namespace Configuration {
static constexpr std::string_view MODEL_PATH =
    "/Users/alvaro/github.com/yolo-object-detection/resources/models/yolov3.weights";
static constexpr std::string_view CONFIG_PATH =
    "/Users/alvaro/github.com/yolo-object-detection/resources/cfg/yolov3.cfg";
static constexpr std::string_view CLASSES_PATH =
    "/Users/alvaro/github.com/yolo-object-detection/resources/classes/object_detection_classes_yolov3.txt";
static constexpr std::string_view FRAMEWORK = "";
static constexpr std::string_view INPUT = "/Users/alvaro/github.com/yolo-object-detection/resources/images/soccer.jpg";
static constexpr float THRESHOLD = 0.5;
static constexpr float NMS_THRESHOLD = 0.4;
static constexpr int BACKEND = 2;
static constexpr int TARGET = 0;
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
