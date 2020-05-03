//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_CAPATVALUEHELPER_H
#define CHAPTER_13_FUNCTORS_CAPATVALUEHELPER_H

#include <iostream>

using namespace std;

template <typename T>
class CapAtValueHelper {
public:
    explicit CapAtValueHelper(const T val) : val(val){}

    bool operator() (const T e1) const {
        return e1 > val;
    }
private:
    const T val;
};

#endif //CHAPTER_13_FUNCTORS_CAPATVALUEHELPER_H
