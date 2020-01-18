#ifndef YOLO_H
#define YOLO_H

#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "configuration.h"
#include "model.h"
#include "postprocessor.h"
#include "preprocessor.h"
#include "queue_fps.h"
#include "window.h"

class Yolo {
 public:
  Yolo();
  ~Yolo();
  void Run();

 private:
  std::unique_ptr<QueueFps<cv::Mat>> frames_;
  std::unique_ptr<QueueFps<cv::Mat>> processed_frames_;
  std::unique_ptr<QueueFps<std::vector<cv::Mat>>> predictions_;
  std::unique_ptr<cv::VideoCapture> capturer_;
  std::unique_ptr<Model> model_;

  std::vector<std::string> classes_;
  std::vector<std::thread> threads_;

  void StartFramesCapture();
  void StartFramesProcessing();

  void CaptureFrames();
  void ProcessFrames();
};

#endif
