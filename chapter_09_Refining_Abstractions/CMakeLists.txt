cmake_minimum_required(VERSION 3.8)
project(chapter_09_Refining_Abstractions)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyVector.h SnakeGame.h PointTale.h AltairModule.h UniquelyIdentified.h RealNumber.h RationalNumber.h RandomGenerator.h)
add_executable(chapter_09_Refining_Abstractions ${SOURCE_FILES})