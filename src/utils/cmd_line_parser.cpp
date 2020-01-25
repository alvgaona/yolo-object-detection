#include "utils/cmd_line_parser.h"

CmdLineParser::CmdLineParser(int argc, const char** argv) {
  this->keys_ =
      "{ help  h               | | Print help message.                               }"
      "{ configuration  c      | | File containing parameters for YOLO algorithm.    }"
      "{ input i               | | Image or video to process (absolute path to file) }";
  this->parser_ = std::make_unique<cv::CommandLineParser>(argc, argv, keys_);
  this->argc_ = argc;
  this->argv_ = argv;
}
