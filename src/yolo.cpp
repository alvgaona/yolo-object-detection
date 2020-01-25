#include "yolo.h"

Yolo::Yolo(struct YoloUtils::FrameProcessingData& data) {
  model_ = nullptr;
  capturer_ = std::make_unique<cv::VideoCapture>();
  frames_ = std::make_unique<QueueFps<cv::Mat>>();
  processed_frames_ = std::make_unique<QueueFps<cv::Mat>>();
  predictions_ = std::make_unique<QueueFps<std::vector<cv::Mat>>>();
  data_ = std::move(data);
}

Yolo::~Yolo() {
  std::for_each(threads_.begin(), threads_.end(), [](std::thread& t) { t.join(); });
}

void Yolo::Run(std::filesystem::path& model_path, std::filesystem::path& config_path,
               std::filesystem::path& classes_path, std::filesystem::path& input_path) {
  Window window("YOLO Object Detection", data_.threshold);
  window.Build();

  LoadClasses(classes_path);

  Model model = Model::Init(cv::String(model_path), cv::String(config_path), data_.nms_threshold);
  model_ = std::make_unique<Model>(std::move(model));

  capturer_->open(cv::String(input_path));

  StartFramesCapture();
  StartFramesProcessing();

  while (cv::waitKey(1) < 0) {
    if (predictions_->Empty()) {
      continue;
    }

    std::vector<cv::Mat> outs = predictions_->Get();
    cv::Mat frame = processed_frames_->Get();

    model_->Process(frame, outs, classes_);

    window.DisplayInfo(frame, frames_->GetFps(), frames_->GetCounter(), predictions_->GetFps(),
                       predictions_->GetCounter());

    window.Show(frame);
  }
}

void Yolo::StartFramesCapture() { threads_.emplace_back(std::thread(&Yolo::CaptureFrames, this)); }

void Yolo::StartFramesProcessing() { threads_.emplace_back(std::thread(&Yolo::ProcessFrames, this)); }

void Yolo::CaptureFrames() {
  cv::Mat frame;

  while (true) {
    *capturer_ >> frame;

    if (!frame.empty()) {
      frames_->Push(frame.clone());
    } else {
      break;
    }
  }
}

void Yolo::ProcessFrames() {
  std::queue<cv::AsyncArray> futures;

  while (true) {
    cv::Mat frame;

    if (!frames_->Empty()) {
      frame = frames_->Get();
    }

    if (!frame.empty()) {
      model_->Process(frame, data_);
      processed_frames_->Push(frame);

      futures.push(model_->ForwardAsync());
    }

    while (!futures.empty() && futures.front().wait_for(std::chrono::seconds(0))) {
      cv::AsyncArray async = futures.front();
      futures.pop();
      cv::Mat out;
      async.get(out);
      predictions_->Push({out});
    }
  }
}

void Yolo::LoadClasses(const std::filesystem::path& filepath) {
  std::ifstream ifs(filepath.string());
  if (!ifs.is_open()) {
    CV_Error(cv::Error::StsError, "File " + filepath.string() + " not found");
  }
  std::string line;
  while (std::getline(ifs, line)) {
    classes_.emplace_back(line);
  }
  ifs.close();
}
