cmake_minimum_required(VERSION 3.8)
project(chapter_16_Introduction_to_Inheritance)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Function.h SimpleFunction.h CompositionFunction.h DerivativeFunction.h)
add_executable(chapter_16_Introduction_to_Inheritance ${SOURCE_FILES})