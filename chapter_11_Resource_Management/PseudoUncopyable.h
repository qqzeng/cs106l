//
// Created by GEORGE-pc on 2020/3/19.
//

#ifndef CHAPTER_11_RESOURCE_MANAGEMENT_PSEUDOUNCOPYABLE_H
#define CHAPTER_11_RESOURCE_MANAGEMENT_PSEUDOUNCOPYABLE_H

#include <cstdlib>

class PseudoUncopyable {
public:
    PseudoUncopyable(){};
    /**
     * 这样设计拷贝构造，会导致在调用时，对象被构造出来，但其字段却没有被正确赋值。
     */
    PseudoUncopyable(const PseudoUncopyable& other) {
        abort();
    }
    PseudoUncopyable& operator= (const PseudoUncopyable& other) {
        abort();
        return *this; // Never reached; suppresses compiler warnings
    }
};

#endif //CHAPTER_11_RESOURCE_MANAGEMENT_PSEUDOUNCOPYABLE_H
