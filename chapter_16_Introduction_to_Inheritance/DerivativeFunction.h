//
// Created by GEORGE-pc on 2020/5/3.
//

#ifndef CHAPTER_16_INTRODUCTION_TO_INHERITANCE_DERIVATIVEFUNCTION_H
#define CHAPTER_16_INTRODUCTION_TO_INHERITANCE_DERIVATIVEFUNCTION_H


#include "Function.h"

class DerivativeFunction : public Function {

public:
    explicit DerivativeFunction(Function* func1, double deltaX) : func1(func1), deltaX(deltaX) {
    }
    virtual double evaluateAt(double value) {
        double result1 = func1->evaluateAt(value + deltaX);
        double result2 = func1->evaluateAt(value - deltaX);
        return (result1 - result2) / (2 * deltaX);
    }
private:
    Function* func1;
    const double deltaX;

};


#endif //CHAPTER_16_INTRODUCTION_TO_INHERITANCE_DERIVATIVEFUNCTION_H
