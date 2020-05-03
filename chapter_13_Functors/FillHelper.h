//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_FILLHELPER_H
#define CHAPTER_13_FUNCTORS_FILLHELPER_H

#include <iostream>
#include <vector>
using namespace std;

class FillHelper {
public:
    explicit FillHelper(const int initVal) : initVal(initVal) {

    }

    int operator()() {
        return ++initVal;
    }

private:
    int initVal;
};


#endif //CHAPTER_13_FUNCTORS_FILLHELPER_H
