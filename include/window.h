#ifndef DISPLAY_H
#define DISPLAY_H

#include <opencv2/opencv.hpp>
#include <string>

class Window {
 public:
    Window(const std::string& name, float confidence_threshold);
    ~Window();

    void Build();
    void Show(cv::Mat& frame);
    void DisplayInfo(unsigned int counter);

private:
    float confidence_threshold_;
    std::string name_;

    void Callback(int pos, void*);
};



#endif
