cmake_minimum_required(VERSION 2.8)
project(patchselector)
find_package(OpenCV REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

add_executable(patchselector main.cpp)
target_link_libraries(patchselector ${OpenCV_LIBS})
