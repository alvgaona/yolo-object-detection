cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(start_cmake_project)

find_package(example 1.0 REQUIRED)

# Add dirs from external packages
include_directories(
    include
)
link_directories(${Example_LIBRARY_DIRS})
add_definitions(${Example_DEFINITIONS})

# Find all executables
file(GLOB SOURCES src/*.cpp)

# Add GoogleTest library subdirectories
add_subdirectory(thirdparty/googletest)

# Add the testing executable
add_executable(test test/utest_start_cmake_project.cpp)

target_link_libraries(test gtest_main)

# Add project executable
add_executable(start_cmake_project ${SOURCES})
target_link_libraries(start_cmake_project ${Example_LIBRARIES})
