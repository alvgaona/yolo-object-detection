#ifndef YOLO_OBJECT_DETECTION_OUTPUT_LAYERS_H
#define YOLO_OBJECT_DETECTION_OUTPUT_LAYERS_H

#include "detection_output.h"
#include "output_layer.h"
#include "region.h"

#include <exception>
#include <memory>
#include <string>

class OutputLayers {
 public:
  OutputLayers() = delete;
  ~OutputLayers() = delete;
  OutputLayers(const OutputLayers& source) = delete;
  OutputLayers(OutputLayers&& source) noexcept = delete;

  OutputLayers& operator=(const OutputLayers& source) = delete;
  OutputLayers& operator=(OutputLayers&& source) noexcept = delete;

  static std::unique_ptr<OutputLayer> of(const std::string& type, float threshold);
};

#endif
