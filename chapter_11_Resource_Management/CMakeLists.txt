cmake_minimum_required(VERSION 3.8)
project(chapter_11_Resource_Management)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector.h Singleton.h PseudoUncopyable.h SmartPointer.h)
add_executable(chapter_11_Resource_Management ${SOURCE_FILES})