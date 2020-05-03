cmake_minimum_required(VERSION 3.8)
project(chapter_13_Functors)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NumberOperation.h BiasedSortHelper.h FillHelper.h ExpungeHelper.h DeviationHelper.h CapAtValueHelper.h BinderOnly.h BindOnly.h UnaryCompose.h Compose.h not1_.h)
add_executable(chapter_13_Functors ${SOURCE_FILES})