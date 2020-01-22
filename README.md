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
- OpenVINO >= 2019_R3.1
- gcc/g++ >= 9.2

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

## Coding style

TBD

## To start using

TBD

## Contributing

TBD

## License

[MIT](./LICENSE)

## Rubric points addressed

### Loops, Functions, I/O

| Point                                                                                          | File            | Lines          |
|------------------------------------------------------------------------------------------------|-----------------|----------------|
| The project demonstrates an understanding of C++ functions and control structures.             |                 |                |
| The project reads data from a file and process the data, or the program writes data to a file. |                 |                |
| The project accepts user input and processes the input.                                        |                 |                |

### Object Oriented Programming

| Point                                                                            | File            | Lines          |
|----------------------------------------------------------------------------------|-----------------|----------------|
| The project uses Object Oriented Programming techniques.                         |                 |                |
| Classes use appropriate access specifiers for class members.                     |                 |                |
| Class constructors utilize member initialization lists.                          |                 |                |
| The project follows the Rule of 5.                                               |                 |                |
| Classes abstract implementation details from their interfaces.                   |                 |                |
| Classes encapsulate behavior.                                                    |                 |                |
| Classes follow an appropriate inheritance hierarchy.                             |                 |                |
| Overloaded functions allow the same function to operate on different parameters. |                 |                |
| Derived class functions override virtual base class functions.                   |                 |                |
| Templates generalize functions in the project.                                   |                 |                |

### Memory Management

| Point                                                                                     | File            | Lines          |
|-------------------------------------------------------------------------------------------|-----------------|----------------|
| The project makes use of references in function declarations.                             |                 |                |
| The project uses destructors appropriately.                                               |                 |                |
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. |                 |                |
| The project follows the Rule of 5.                                                        | all             |                |
| The project uses move semantics to move data, instead of copying it, where possible.      |                 |                |
| The project uses smart pointers instead of raw pointers.                                  |                 |                | 

### Concurrency

| Point                                        | File            | Lines          |
|----------------------------------------------|-----------------|----------------|
| The project uses multithreading.             | [yolo.cpp]      | 27, 28, 47, 49 |
| A promise and future is used in the project. | -               | -              |
| A mutex or lock is used in the project.      | [queue_fps.h]   | 25, 36, 48, 64 |
| A condition variable is used in the project. | -               | -              |   


[yolo.cpp]: ./src/yolo.cpp
[queue_fps.h]: ./include/queue_fps.h
