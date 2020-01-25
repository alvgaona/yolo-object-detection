#ifndef YOLO_OBJECT_DETECTION_YOLO_H
#define YOLO_OBJECT_DETECTION_YOLO_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "utils/yolo_utils.h"
#include "model/model.h"
#include "model/postprocessor.h"
#include "model/preprocessor.h"
#include "queue_fps.h"
#include "gui/window.h"

class Yolo {
 public:
  Yolo() = delete;
  Yolo(struct YoloUtils::FrameProcessingData& data);
  ~Yolo();
  Yolo(const Yolo& source) = delete;
  Yolo(Yolo&& source) noexcept = delete;

  Yolo& operator=(const Yolo& source) = delete;
  Yolo& operator=(Yolo&& source) noexcept = delete;


  void Run(std::filesystem::path& model_path, std::filesystem::path& config_path, std::filesystem::path& classes_path,
           std::filesystem::path& input_path);

 private:
  std::unique_ptr<QueueFps<cv::Mat>> frames_;
  std::unique_ptr<QueueFps<cv::Mat>> processed_frames_;
  std::unique_ptr<QueueFps<std::vector<cv::Mat>>> predictions_;
  std::unique_ptr<cv::VideoCapture> capturer_;
  std::unique_ptr<Model> model_;

  std::vector<std::string> classes_;
  std::vector<std::thread> threads_;

  YoloUtils::FrameProcessingData data_;

  void StartFramesCapture();
  void StartFramesProcessing();

  void CaptureFrames();
  void ProcessFrames();

  void LoadClasses(const std::filesystem::path& filepath);
};

#endif
