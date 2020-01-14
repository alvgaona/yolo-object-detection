#include "window.h"

Window::Window(const std::string& name, float confidence_threshold) {
  this->confidence_threshold_ = static_cast<int>(confidence_threshold * 100);
  this->name_ = name;
}

Window::~Window() {}

void Window::Build() {
  cv::namedWindow(name_, cv::WINDOW_NORMAL);
  cv::createTrackbar("Confidence threshold, %", name_, &confidence_threshold_, 99, Callback);
}

void Window::Callback(int pos, void*) { confidence_threshold_ = pos * 0.01f; }

void Window::Show(cv::Mat& frame) { cv::imshow(name_, frame); }

// TODO: Implement
void Window::DisplayInfo(unsigned int counter) {}
