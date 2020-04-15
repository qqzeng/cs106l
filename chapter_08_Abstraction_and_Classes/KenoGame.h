
//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_08_ABSTRACTION_AND_CLASSES_KENOGAME_H
#define CHAPTER_08_ABSTRACTION_AND_CLASSES_KENOGAME_H

#include <vector>
#include <set>

using namespace std;

class KenoGame {
public:
    KenoGame();

    void addNumber(int value);
    size_t numChosen();

    size_t numWinners(vector<int>& values);

private:
    set<int> numbers;
};

#endif //CHAPTER_08_ABSTRACTION_AND_CLASSES_KENOGAME_H
