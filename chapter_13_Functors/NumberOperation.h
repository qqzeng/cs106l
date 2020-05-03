//
// Created by GEORGE-pc on 2020/5/1.
//

#ifndef CHAPTER_13_FUNCTORS_NUMBEROPERATION_H
#define CHAPTER_13_FUNCTORS_NUMBEROPERATION_H


template <typename T>
class NumberOperation {
public:
    NumberOperation(T initVal) : initSum(initVal) {}
T operator() (const T &ele) {
    return initSum += ele;
}
const T get() const {
    return initSum;
}
private:
T initSum;
};


#endif //CHAPTER_13_FUNCTORS_NUMBEROPERATION_H
