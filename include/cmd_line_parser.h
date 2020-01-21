#ifndef YOLO_OBJECT_DETECTION_CMD_LINE_PARSER_H
#define YOLO_OBJECT_DETECTION_CMD_LINE_PARSER_H

#include <opencv2/core.hpp>
#include <string>

class CmdLineParser {
 public:
  CmdLineParser(int argc, const char* argv[]);
  ~CmdLineParser() = default;

  template <typename T>
  T Get(const std::string& cmd) {
    return parser_->get<T>(cmd);
  }

 private:
  int argc_;
  const char** argv_;
  std::unique_ptr<cv::CommandLineParser> parser_;
  std::string keys_;
};

#endif
