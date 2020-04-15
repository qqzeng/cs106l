//
// Created by GEORGE-pc on 2020/3/17.
//

#include "KenoGame.h"

KenoGame::KenoGame() {

}

void KenoGame::addNumber(int value) {
    numbers.insert(value);
}

size_t KenoGame::numChosen() {
    return numbers.size();
}

size_t KenoGame::numWinners(vector<int> &values) {
    size_t num_winners = 0;
    for (size_t i = 0; i < values.size(); ++i) {
        if (numbers.count(values[i]) == 1) {
            num_winners++;
        }
    }
    return num_winners;
}




