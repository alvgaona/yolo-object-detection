# YOLO Object Detection

This project is the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
It aims to detect objects from an image or sequence of frames from a video by using the You Only Look Once (YOLO) Deep Neural Network.

Furthermore, this project follows Object Oriented Programming (OOP) and the latest C++ features by using
STL threads, locks, smart pointers and whatnot.

## Installation

This project's core is OpenCV and the Intel Inference Engine from OpenVINO.
In which you can find more documentation about these two projects in [here](https://opencv.org/) and [here](https://software.intel.com/en-us/openvino-toolkit) respectively.

### Supported Operating Systems

OpenCV is supported in almost every operating system. On the other hand, OpenVINO only supports Linux and 
macOS up to version 10.13. Nevertheless, this project works for 10.15 as well.

- Ubuntu 16.04 LTS or later.
- macOS 10.15.

### Dependencies

- cmake >= 3.11
- make >= 4.2 (Linux, Mac)
- OpenCV >= 4.1.2
- OpenVINO == 2019_R3.1
- gcc/g++ == 9.2

### Requisites

#### Models

Model weights can be downloaded with this [script](https://github.com/opencv/opencv_extra/blob/master/testdata/dnn/download_models.py).

```bash
python3 download_models.py
```

A good place to store these models is `resources/` under a `models/` directory that you have to create.

#### OpenCV and OpenVINO.

TBD

### Build instructions

1. Clone this repo.

With SSH

```bash
git clone git@github.com:alvgaona/yolo-object-detection.git --recurse-submodules
```

With HTTPS

```bash
git clone https://github.com/alvgaona/yolo-object-detection.git --recurse-submodules
```

This project relies on [googletest](https://github.com/abseil/googletest.git) as a thirdparty library.

2. Compile the project.

```bash
make build
```

Look into the [Makefile](./Makefile) to see how the app is built.

3. Run it.

```bash
 ./build/yolo_object_detection \
  --model="<prefix>/yolo-object-detection/resources/models/yolov3.weights" \
  --config="<prefix>/yolo-object-detection/resources/cfg/yolov3.cfg" \
  --classes="<prefix>/yolo-object-detection/resources/classes/object_detection_classes_yolov3.txt" \
  --input="<prefix>/yolo-object-detection/resources/videos/overpass.mp4"
```

## Tests

TBD

## To start using

TBD

## Contributing

TBD

## License

[MIT](./LICENSE)
