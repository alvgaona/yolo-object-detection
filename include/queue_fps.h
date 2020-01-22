#ifndef YOLO_OBJECT_DETECTION_QUEUE_FPS_H
#define YOLO_OBJECT_DETECTION_QUEUE_FPS_H

#include <mutex>
#include <queue>

#include <opencv2/core.hpp>

template <typename T>
class QueueFps : private std::queue<T> {
 public:
  QueueFps();
  ~QueueFps();
  QueueFps(const QueueFps& source) = delete;
  QueueFps(QueueFps&& source) noexcept = delete;

  QueueFps& operator=(const QueueFps& source) = delete;
  QueueFps& operator=(QueueFps&& source) noexcept = delete;

  unsigned int GetCounter() { return counter_; }

  void Push(const T& entry);
  T Get();
  bool Empty();
  float GetFps();
  void Clear();

 private:
  cv::TickMeter tick_meter_;
  std::mutex mutex_;
  unsigned int counter_;
};

template <typename T>
QueueFps<T>::QueueFps() : counter_(0) {}

template <typename T>
QueueFps<T>::~QueueFps() {}

template <typename T>
void QueueFps<T>::Push(const T& entry) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::queue<T>::push(entry);
  counter_++;

  if (counter_ == 1) {
    tick_meter_.reset();
    tick_meter_.start();
  }
}

template <typename T>
T QueueFps<T>::Get() {
  std::lock_guard<std::mutex> lock(mutex_);
  T entry = this->front();
  this->pop();
  return entry;
}

template <typename T>
float QueueFps<T>::GetFps() {
  tick_meter_.stop();
  double fps = counter_ / tick_meter_.getTimeSec();
  tick_meter_.start();
  return static_cast<float>(fps);
}

template <typename T>
void QueueFps<T>::Clear() {
  std::lock_guard<std::mutex> lock(mutex_);
  while (!this->empty()) this->pop();
}
template <typename T>
bool QueueFps<T>::Empty() {
  return this->empty();
}

#endif
