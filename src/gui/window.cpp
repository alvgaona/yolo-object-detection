#include "gui/window.h"

int Window::confidence_threshold_;

Window::Window(const std::string& name, float confidence_threshold) {
  confidence_threshold_ = static_cast<int>(confidence_threshold * 100);
  this->name_ = name;
}

void Window::Build() {
  cv::namedWindow(name_, cv::WINDOW_NORMAL);
  cv::createTrackbar("Confidence threshold, %", name_, &Window::confidence_threshold_, 99, OnChange);
}

void Window::OnChange(int pos, void*) { confidence_threshold_ = pos * 0.01f; }

void Window::Show(cv::Mat& frame) { cv::imshow(name_, frame); }

void Window::DisplayInfo(cv::Mat& frame, float frames_fps, unsigned int frames_counter, float predictions_fps,
                         unsigned int predictions_counter) {
  if (predictions_counter > 1) {
    std::string label = cv::format("Camera: %.2f FPS", frames_fps);
    putText(frame, label, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));

    label = cv::format("Network: %.2f FPS", predictions_fps);
    putText(frame, label, cv::Point(0, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));

    label = cv::format("Skipped frames: %d", frames_counter - predictions_counter);
    putText(frame, label, cv::Point(0, 45), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
  }
}
