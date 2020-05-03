//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_NOT1_H
#define CHAPTER_13_FUNCTORS_NOT1_H

#include <functional>
#include "Compose.h"

template <typename UnaryFunction1>
UnaryCompose<UnaryFunction1, logical_not<bool>>
not1_(const UnaryFunction1 &fn1) {
    return Compose(fn1, logical_not<bool>());
}

#endif //CHAPTER_13_FUNCTORS_NOT1_H
