//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_DEVIATIONHELPER_H
#define CHAPTER_13_FUNCTORS_DEVIATIONHELPER_H


#include <iostream>

using namespace std;

class DeviationHelper {
public:
    explicit DeviationHelper(const double mean) : mean(mean){}

    double operator() (double accumulator, const double v1) {
        return accumulator += (v1 - mean) * (v1 - mean);
    }
private:
    double mean;
};

#endif //CHAPTER_13_FUNCTORS_DEVIATIONHELPER_H
