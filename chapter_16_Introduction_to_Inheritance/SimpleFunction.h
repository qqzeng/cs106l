//
// Created by GEORGE-pc on 2020/5/3.
//

#ifndef CHAPTER_16_INTRODUCTION_TO_INHERITANCE_SIMPLEFUNCTION_H
#define CHAPTER_16_INTRODUCTION_TO_INHERITANCE_SIMPLEFUNCTION_H

#include "Function.h"

class SimpleFunction : public Function {

public:

    explicit SimpleFunction(double (* func) (double)) : func(func) {
    }
    virtual double evaluateAt(double value) {
        return func(value);
    }
private:
    double (*func)(double);
};

#endif //CHAPTER_16_INTRODUCTION_TO_INHERITANCE_SIMPLEFUNCTION_H
