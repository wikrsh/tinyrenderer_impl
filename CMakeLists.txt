cmake_minimum_required(VERSION 3.17)
project(tinyrenderer_impl)

set(CMAKE_CXX_STANDARD 17)

add_executable(tinyrenderer_impl src/main.cpp src/tgaimage.h src/tgaimage.cpp src/Model.cpp src/Model.h src/geometry.h src/renderer.cpp src/renderer.h)
