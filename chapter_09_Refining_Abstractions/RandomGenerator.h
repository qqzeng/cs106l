//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_RANDOMGENERATOR_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_RANDOMGENERATOR_H

/* Exercise 27. */

#include <ctime>
#include <cstdlib>

class RandomGenerator {

public:
    double next() const;

private:
    static bool isSeeded;

};

bool RandomGenerator::isSeeded;

double RandomGenerator::next() const {
    if (!isSeeded) {
        srand(static_cast<unsigned int>(time(NULL)));
        isSeeded = true;
    }
    return static_cast<double >(rand()) / (RAND_MAX + 1);
}

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_RANDOMGENERATOR_H
