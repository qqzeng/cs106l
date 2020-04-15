cmake_minimum_required(VERSION 3.8)
project(chapter_04_Multi-File_Programs_Abstraction_and_Preprocessor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp color.h units.h)
add_executable(chapter_04_Multi-File_Programs_Abstraction_and_Preprocessor ${SOURCE_FILES})