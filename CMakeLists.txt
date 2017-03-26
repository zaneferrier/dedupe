cmake_minimum_required(VERSION 2.6)
project(dedupe)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_COMPILER /usr/bin/g++-6)
add_executable(dedupe main.cpp)

install(TARGETS dedupe RUNTIME DESTINATION bin)
