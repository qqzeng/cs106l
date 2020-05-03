//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_COMPOSE_H
#define CHAPTER_13_FUNCTORS_COMPOSE_H


#include "UnaryCompose.h"

template <typename UnaryFunction1, typename UnaryFunction2>
UnaryCompose<UnaryFunction1, UnaryFunction2>
Compose(const UnaryFunction1 &fn1, const UnaryFunction2 &fn2) {
    return UnaryCompose<UnaryFunction1, UnaryFunction2>(fn1, fn2);
}

#endif //CHAPTER_13_FUNCTORS_COMPOSE_H
