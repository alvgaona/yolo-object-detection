#ifndef YOLO_OBJECT_DETECTION_WINDOW_H
#define YOLO_OBJECT_DETECTION_WINDOW_H

#include <opencv2/opencv.hpp>

#include <string>

class Window {
 public:
  Window(const std::string& name, float confidence_threshold);
  ~Window() = default;
  Window(const Window& source) = delete;
  Window(Window&& source) noexcept = delete;

  Window& operator=(const Window& source) = delete;
  Window& operator=(Window&& source) noexcept = delete;

  void Build();
  void Show(cv::Mat& frame);
  void DisplayInfo(cv::Mat& frame, float frames_fps, unsigned int frames_counter, float predictions_fps,
                   unsigned int predictions_counter);

 private:
  static int confidence_threshold_;
  std::string name_;

  static void OnChange(int pos, void*);
};

#endif
