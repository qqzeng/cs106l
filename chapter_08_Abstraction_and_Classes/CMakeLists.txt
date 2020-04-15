cmake_minimum_required(VERSION 3.8)
project(chapter_08_Abstraction_and_Classes)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GroceryList.h GroceryList.cpp KenoGame.h KenoGame.cpp)
add_executable(chapter_08_Abstraction_and_Classes ${SOURCE_FILES})