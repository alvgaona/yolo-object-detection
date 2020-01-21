#include "cmd_line_parser.h"

CmdLineParser::CmdLineParser(int argc, const char** argv) {
  this->keys_ = "{ help  h     | | Print help message. }"
                "{ model       | | Model weights }"
                "{ config      | | Model configuration file (absolute path) }"
                "{ input i     | | Path to input image or video file. Skip this argument to capture frames from a camera. }"
                "{ classes     | | Optional path to a text file with names of classes to label detected objects. }";
  this->parser_ = std::make_unique<cv::CommandLineParser>(argc, argv, keys_);
  this->argc_ = argc;
  this->argv_ = argv;
}
