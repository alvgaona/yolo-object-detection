#include <yaml-cpp/yaml.h>

#include "yolo.h"
#include "utils/cmd_line_parser.h"
#include "utils/yolo_utils.h"

int main(int argc, const char* argv[]) {
  CmdLineParser parser(argc, argv);

  std::filesystem::path conf = YoloUtils::FindFile(parser.Get<std::string>("configuration")).value();
  YAML::Node yaml_node = YAML::LoadFile(conf.string());

  std::filesystem::path weights = YoloUtils::FindFile(yaml_node["weights"].as<std::string>()).value();
  std::filesystem::path cfg = YoloUtils::FindFile(yaml_node["cfg"].as<std::string>()).value();
  std::filesystem::path classes = YoloUtils::FindFile(yaml_node["classes"].as<std::string>()).value();

  std::filesystem::path input(parser.Get<std::string>("input"));

  YoloUtils::FrameProcessingData data;
  data.mean =
      cv::Scalar(yaml_node["mean1"].as<double>(), yaml_node["mean2"].as<double>(), yaml_node["mean3"].as<double>());
  data.rgb = yaml_node["rgb"].as<bool>();
  data.scale = yaml_node["scale"].as<float>();
  data.input_size = cv::Size(yaml_node["width"].as<int>(), yaml_node["height"].as<int>());
  data.nms_threshold = yaml_node["nms_threshold"].as<float>();
  data.threshold = yaml_node["threshold"].as<float>();

  Yolo yolo(data);
  yolo.Run(weights, cfg, classes, input);

  return 0;
}
