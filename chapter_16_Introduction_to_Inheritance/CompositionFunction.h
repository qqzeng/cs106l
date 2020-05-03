//
// Created by GEORGE-pc on 2020/5/3.
//

#ifndef CHAPTER_16_INTRODUCTION_TO_INHERITANCE_COMPOSITIONFUNCTION_H
#define CHAPTER_16_INTRODUCTION_TO_INHERITANCE_COMPOSITIONFUNCTION_H

#include "Function.h"

class CompositionFunction : public Function {

public:
    explicit CompositionFunction(Function* func1, Function* func2) : func1(func1), func2(func2) {
    }
    virtual double evaluateAt(double value) {
        return func1->evaluateAt(func2->evaluateAt(value));
    }
private:
    Function* func1;
    Function* func2;

};


#endif //CHAPTER_16_INTRODUCTION_TO_INHERITANCE_COMPOSITIONFUNCTION_H
