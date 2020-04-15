//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_RATIONNUMBER_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_RATIONNUMBER_H

class RationalNumber
{
public:
    RationalNumber(int num = 0, int denom = 1) :
            numerator(num), denominator(denom) {}

    double getValue() const {
        return static_cast<double>(numerator) / denominator;
    }
    void setNumerator(int value) {
        numerator = value;
    }
    void setDenominator(int value) {
        denominator = value;
    }
private:
    int numerator, denominator;
};

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_RATIONNUMBER_H
