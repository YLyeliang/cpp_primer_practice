cmake_minimum_required(VERSION 3.17)
project(now_code)

set(CMAKE_CXX_STANDARD 14)

#find_library(OpenCV)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 14)

add_executable(now_code chapter7/73_head.h chapter7/73_additional_class_feature.cpp)

target_link_libraries(now_code ${OpenCV_LIBS})