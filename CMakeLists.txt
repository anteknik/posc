cmake_minimum_required(VERSION 3.10)

project(test_cplus)

set(CMAKE_CXX_STANDARD 17)

add_executable(menu WIN32 main.cpp ATM.cpp)
