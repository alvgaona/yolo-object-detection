#include "model.h"

Model::~Model() = default;

Model::Model(cv::dnn::Net& net, Postprocessor& postprocessor, Preprocessor& preprocessor) {
  net_ = std::make_unique<cv::dnn::Net>(std::move(net));
  postprocessor_ = std::make_unique<Postprocessor>(std::move(postprocessor));
  preprocessor_ = std::make_unique<Preprocessor>(std::move(preprocessor));
}

Model::Model(Model&& source) noexcept {
  net_ = std::move(source.net_);
  preprocessor_ = std::move(source.preprocessor_);
  postprocessor_ = std::move(source.postprocessor_);

  source.net_ = nullptr;
  source.preprocessor_ = nullptr;
  source.postprocessor_ = nullptr;
}

void Model::process(cv::Mat& frame, const std::vector<cv::Mat>& outlayers, const std::vector<std::string>& classes) {
  std::vector<cv::String> outlayer_names = net_->getUnconnectedOutLayersNames();
  postprocessor_->process(frame, *net_, outlayers, classes);
}

void Model::process(cv::Mat& frame, struct Configuration::FrameProcessingData& data) { preprocessor_->process(frame, *net_, data); }

Model Model::Init(const cv::String& model, const cv::String& config, const cv::String& framework,
                  cv::dnn::Backend backend, cv::dnn::Target target) {
  cv::dnn::Net net = cv::dnn::readNet(model, config, framework);
  net.setPreferableBackend(backend);
  net.setPreferableTarget(target);

  Postprocessor postprocessor;
  Preprocessor preprocessor;

  return Model(net, postprocessor, preprocessor);
}

cv::AsyncArray Model::ForwardAsync() { return net_->forwardAsync(); }

Model& Model::operator=(Model&& source) noexcept {
  net_ = std::move(source.net_);
  preprocessor_ = std::move(source.preprocessor_);
  postprocessor_ = std::move(source.postprocessor_);

  source.net_ = nullptr;
  source.preprocessor_ = nullptr;
  source.postprocessor_ = nullptr;

  return *this;
}
