cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(yolo_object_detection)

find_package(opencv 4.1 REQUIRED)

# Find all executables
file(GLOB SOURCES src/*.cpp)

# Add GoogleTest library subdirectories
add_subdirectory(thirdparty/googletest)

# Add the testing executable
add_executable(test test/utest_queue_fps.cpp)

target_link_libraries(test gtest_main)

# Add project executable
add_executable(yolo_object_detection ${SOURCES})
target_link_libraries(yolo_object_detection ${OpenCV_LIBRARIES})

target_include_directories(yolo_object_detection PUBLIC
    include
    ${OpenCV_INCLUDE_DIRS}
    )

link_directories(${OpenCV_LIBRARY_DIRS})
target_compile_definitions(yolo_object_detection PUBLIC ${OpenCV_DEFINITIONS})
