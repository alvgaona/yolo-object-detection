#ifndef YOLO_OBJECT_DETECTION_MODEL_H
#define YOLO_OBJECT_DETECTION_MODEL_H

#include <opencv2/core.hpp>
#include <opencv2/dnn.hpp>

#include "configuration.h"
#include "postprocessor.h"
#include "preprocessor.h"

class Model {
 public:
  Model() = delete;
  ~Model();
  Model(const Model& source) = delete;
  Model(Model&& source) noexcept;

  Model& operator=(const Model& source) = delete;
  Model& operator=(Model&& source) noexcept;

  static Model Init(const cv::String& model, const cv::String& config, const cv::String& framework = "",
                    cv::dnn::Backend backend = cv::dnn::DNN_BACKEND_INFERENCE_ENGINE, cv::dnn::Target target = cv::dnn::DNN_TARGET_CPU);

  void process(cv::Mat& frame, struct Configuration::FrameProcessingData& data);
  void process(cv::Mat& frame, const std::vector<cv::Mat>& outlayers, const std::vector<std::string>& classes);
  cv::AsyncArray ForwardAsync();


 private:
  Model(cv::dnn::Net& net, Postprocessor& postprocessor, Preprocessor& pre);

  std::unique_ptr<cv::dnn::Net> net_;
  std::unique_ptr<Postprocessor> postprocessor_;
  std::unique_ptr<Preprocessor> preprocessor_;
};

#endif
