//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_EXPUNGEHELPER_H
#define CHAPTER_13_FUNCTORS_EXPUNGEHELPER_H

#include <iostream>

using namespace std;

class ExpungeHelper {
public:
    explicit ExpungeHelper(const char ch) : ch(ch) {}
    bool operator() (const string &ele) {
        return ele.find(ch, 0) != string::npos ;
    }
private:
    const char ch;
};


#endif //CHAPTER_13_FUNCTORS_EXPUNGEHELPER_H
