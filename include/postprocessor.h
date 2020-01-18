#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#include "configuration.h"

class Postprocessor {
 public:
  Postprocessor() = default;
  ~Postprocessor() = default;

  Postprocessor(Postprocessor&& source) noexcept ;

  void process(cv::Mat& frame, cv::dnn::Net& net, const std::vector<cv::Mat>& prediction_outputs,
               const std::vector<std::string>& classes);

 private:
  void drawPred(const std::vector<std::string>& classes, int classId, float conf, int left, int top, int right,
                int bottom, cv::Mat& frame);
};

#endif