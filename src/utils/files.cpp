#include "utils/files.h"

std::optional<std::filesystem::path> Files::FindFile(const std::string& filename) {
  for (auto& p : std::filesystem::recursive_directory_iterator(std::filesystem::current_path())) {
    if(p.path().filename().string() == filename) {
      return std::optional<std::filesystem::path>{p.path()};
    }
  }
  return std::nullopt;
}
