cmake_minimum_required(VERSION 2.6)
project(dedupe)

add_executable(dedupe main.cpp)

install(TARGETS dedupe RUNTIME DESTINATION bin)
