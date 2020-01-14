#ifndef QUEUE_FPS_H
#define QUEUE_FPS_H

#include <mutex>
#include <opencv2/core.hpp>
#include <queue>

template <typename T>
class QueueFps : private std::queue<T> {
 public:
  QueueFps();
  ~QueueFps();

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

#endif
