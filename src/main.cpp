#include "yolo.h"
#include "cmd_line_parser.h"

int main(int argc, const char* argv[]) {
  CmdLineParser parser(argc, argv);

  std::filesystem::path model(parser.Get<std::string>("model"));
  std::filesystem::path config(parser.Get<std::string>("config"));
  std::filesystem::path classes(parser.Get<std::string>("classes"));
  std::filesystem::path input(parser.Get<std::string>("input"));

  Yolo yolo;
  yolo.Run(model, config, classes, input);

  return 0;
}
