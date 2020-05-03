//
// Created by GEORGE-pc on 2020/5/2.
//

#ifndef CHAPTER_13_FUNCTORS_BINDERONLY_H
#define CHAPTER_13_FUNCTORS_BINDERONLY_H

#include <functional>

using namespace std;

template <typename UnaryFunction> class BinderOnly  :
        public unary_function<typename UnaryFunction::argument_type,
                typename UnaryFunction::result_type>
{
public:
    BinderOnly(const UnaryFunction& fn,
               const typename UnaryFunction::argument_type& value) : function1(fn), value(value){}

    typename UnaryFunction::result_type operator() (const typename UnaryFunction::argument_type& dumy) const {
        return function1(value);
    }

private:
    UnaryFunction function1;
    typename UnaryFunction::argument_type value;
};


#endif //CHAPTER_13_FUNCTORS_BINDERONLY_H
