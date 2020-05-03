cmake_minimum_required(VERSION 3.8)
project(chapter_12_Error_Handling)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AutomaticStackManager.h)
add_executable(chapter_12_Error_Handling ${SOURCE_FILES})