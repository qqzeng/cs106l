//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_BIASEDSORTHELPER_H
#define CHAPTER_13_FUNCTORS_BIASEDSORTHELPER_H

#include <iostream>
#include <vector>
using namespace std;

class BiasedSortHelper {
public:
    explicit BiasedSortHelper(const string &winner) : winner(winner) {

    }
    bool operator()(const string &str1, const string &str2) const {
        if (str1 != winner && str2 != winner) return str1 < str2;
        if (str1 == winner && str2 == winner) return false;
        if (str1 == winner) return true;
        return false;
    }

private:
    const string winner;
};


#endif //CHAPTER_13_FUNCTORS_BIASEDSORTHELPER_H
