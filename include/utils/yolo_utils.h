#ifndef YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H
#define YOLO_OBJECT_DETECTION_CONFIGURATION_MANAGER_H

#include <opencv2/core.hpp>

#include <filesystem>
#include <optional>
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

static std::optional<std::filesystem::path> FindFile(const std::string& filename) {
  for (auto& p : std::filesystem::recursive_directory_iterator(std::filesystem::current_path())) {
    if (p.path().filename().string() == filename) {
      return std::optional<std::filesystem::path>{p.path()};
    }
  }
  return std::nullopt;
}
}  // namespace YoloUtils

#endif
