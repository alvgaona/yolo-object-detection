#include "model/preprocessor.h"

Preprocessor::Preprocessor(Preprocessor&& source) noexcept {}

void Preprocessor::Process(cv::Mat& frame, cv::dnn::Net& net, struct YoloUtils::FrameProcessingData& data){
  static cv::Mat blob;

  if (data.input_size.width <= 0) {
    data.input_size.width = frame.cols;
  }
  if (data.input_size.height <= 0) {
    data.input_size.height = frame.rows;
  }

  cv::dnn::blobFromImage(frame, blob, 1.0, data.input_size, cv::Scalar(), data.rgb, false, CV_8U);

  net.setInput(blob, "", data.scale, data.mean);
  if (net.getLayer(0)->outputNameToIndex("im_info") != -1)
  {
    cv::resize(frame, frame, data.input_size);
    cv::Mat imInfo = (cv::Mat_<float>(1, 3) << data.input_size.height, data.input_size.width, 1.6f);
    net.setInput(imInfo, "im_info");
  }
}
