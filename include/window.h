#ifndef WINDOW_H
#define WINDOW_H

#include <opencv2/opencv.hpp>
#include <string>

class Window {
 public:
  Window(const std::string& name, float confidence_threshold);
  ~Window() = default;

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
