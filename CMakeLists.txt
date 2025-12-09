cmake_minimum_required(VERSION 3.10)

project(test_cplus)

set(CMAKE_CXX_STANDARD 17)

include_directories(library)
add_executable(menu WIN32 src/main.cpp src/ATM.cpp)
