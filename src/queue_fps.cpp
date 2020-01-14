#include "queue_fps.h"

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
