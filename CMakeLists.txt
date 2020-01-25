cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(yolo_object_detection)

find_package(OpenCV 4.1.2 REQUIRED)
find_package(yaml-cpp 0.6.3 REQUIRED)

file(GLOB SOURCES
    src/*.cpp
    src/gui/**.cpp
    src/model/**.cpp
    src/utils/**.cpp)

add_subdirectory(thirdparty/googletest)

add_executable(test test/utest_placeholder.cpp)
target_link_libraries(test gtest_main)

add_executable(yolo_object_detection ${SOURCES})
target_link_libraries(yolo_object_detection ${OpenCV_LIBRARIES} ${YAML_CPP_LIBRARIES})
target_include_directories(yolo_object_detection PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIR}
)
target_link_directories(yolo_object_detection PRIVATE ${OpenCV_LIBRARY_DIRS})
target_compile_definitions(yolo_object_detection PRIVATE ${OpenCV_DEFINITIONS})
