#ifndef YOLO_OBJECT_DETECTION_FILES_H
#define YOLO_OBJECT_DETECTION_FILES_H

#include <filesystem>
#include <optional>

class Files {
 public:
    Files() = delete;
    ~Files() = delete;

    static std::optional<std::filesystem::path> FindFile(const std::string& filename);
};



#endif
