//
// Created by GEORGE-pc on 2020/3/9.
//

//#ifndef CHAPTER_02_COLOR_H
//#define CHAPTER_02_COLOR_H
//
//
//
//#endif //CHAPTER_02_COLOR_H

//DEFINE_COLOR(Red, Cyan)
//DEFINE_COLOR(Cyan, Red)
//DEFINE_COLOR(Green, Magenta)
//DEFINE_COLOR(Magenta, Green)
//DEFINE_COLOR(Blue, Yellow)
//DEFINE_COLOR(Yellow, Blue)

// Solution of Exercise-11.
#ifndef  DEFINE_COLOR
#error "Must define macro DEFINE_COLOR before including this header file."
#else
DEFINE_COLOR(Red, Cyan)
DEFINE_COLOR(Cyan, Red)
DEFINE_COLOR(Green, Magenta)
DEFINE_COLOR(Magenta, Green)
DEFINE_COLOR(Blue, Yellow)
DEFINE_COLOR(Yellow, Blue)
#endif
