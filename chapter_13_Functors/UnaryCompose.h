//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_UNARYCOMPOSE_H
#define CHAPTER_13_FUNCTORS_UNARYCOMPOSE_H

#include <functional>

using namespace std;

template <typename UnaryFunction1, typename UnaryFunction2> class UnaryCompose  :
        public unary_function<typename UnaryFunction1::argument_type,
                typename UnaryFunction2::result_type>
{
public:
    UnaryCompose(const UnaryFunction1& fn1, const UnaryFunction2& fn2) : function1(fn1), function2(fn2){}

    typename UnaryFunction2::result_type operator() (const typename UnaryFunction1::argument_type& value) const {
        return function2(function1(value));
    }

private:
    UnaryFunction1 function1;
    UnaryFunction2 function2;
};

#endif //CHAPTER_13_FUNCTORS_UNARYCOMPOSE_H
