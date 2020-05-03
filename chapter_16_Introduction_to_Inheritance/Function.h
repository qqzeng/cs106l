//
// Created by GEORGE-pc on 2020/5/3.
//

#ifndef CHAPTER_16_INTRODUCTION_TO_INHERITANCE_FUNCTION_H
#define CHAPTER_16_INTRODUCTION_TO_INHERITANCE_FUNCTION_H


class Function
{
public:
    virtual ~Function() = 0;
    virtual double evaluateAt(double value) = 0;
};

Function::~Function() {

}

#endif //CHAPTER_16_INTRODUCTION_TO_INHERITANCE_FUNCTION_H
