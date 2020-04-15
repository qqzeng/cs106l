//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_UNIQUELYIDENTIFIED_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_UNIQUELYIDENTIFIED_H

/* Exercise 26. */

#include <iostream>
class UniquelyIdentified {
public:
    UniquelyIdentified();
    static const int getUniqueID();
private:
    static int id;

};

int UniquelyIdentified::id;

UniquelyIdentified::UniquelyIdentified() {
    std::cout << "id: " << id << endl;
    id += 1;
}

const int UniquelyIdentified::getUniqueID() {
    return id;
}

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_UNIQUELYIDENTIFIED_H
