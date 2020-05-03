//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_BINDONLY_H
#define CHAPTER_13_FUNCTORS_BINDONLY_H

#include "BinderOnly.h"

template <typename UnaryFunction>
BinderOnly<UnaryFunction>
BindOnly(const UnaryFunction &fn,
         const typename UnaryFunction::argument_type& value) {
    return BinderOnly<UnaryFunction>(fn, value);
}


#endif //CHAPTER_13_FUNCTORS_BINDONLY_H
