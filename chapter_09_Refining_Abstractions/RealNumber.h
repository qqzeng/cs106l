//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_REALNUMBER_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_REALNUMBER_H

#include "RationalNumber.h"

class RealNumber {
public:
    RealNumber(double number = 0);
    RealNumber(RationalNumber rn) : number(rn.getValue()) {};

    double getValue() { return number; }
private:
    double number;
};

RealNumber::RealNumber(double number) : number(number) {
}

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_REALNUMBER_H
