#include "model/output_layers.h"

std::unique_ptr<OutputLayer> OutputLayers::of(const std::string& type, float threshold) {
  if (type == "DetectionOutput") {
    return std::make_unique<DetectionOutput>(threshold);
  } else if (type == "Region") {
    return std::make_unique<Region>(threshold);
  } else {
    throw std::runtime_error("Unsupported output layer type");
  }
}
