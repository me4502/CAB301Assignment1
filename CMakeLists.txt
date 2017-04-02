cmake_minimum_required(VERSION 3.7)
project(CAB301Assignment1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(Assignment ${SOURCE_FILES})
add_executable(Assignment_Timings ${SOURCE_FILES})
add_executable(Assignment_Logging ${SOURCE_FILES})

target_compile_definitions(Assignment_Timings PRIVATE TIMING=1)
target_compile_definitions(Assignment_Logging PRIVATE LOGGING=1)
