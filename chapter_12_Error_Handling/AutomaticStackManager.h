//
// Created by GEORGE-pc on 2020/5/1.
//

#ifndef CHAPTER_12_ERROR_HANDLING_AUTOMATICSTACKMANAGER_H
#define CHAPTER_12_ERROR_HANDLING_AUTOMATICSTACKMANAGER_H

#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class AutomaticStackManager {
public:
    explicit AutomaticStackManager(stack<T> &myStack);
    ~AutomaticStackManager();

private:
    const T ele;
    stack<T>& s;
};

template <typename T>
AutomaticStackManager<T>::AutomaticStackManager(stack<T> &myStack) :
    s(myStack), ele(myStack.top()) {
    if (myStack.empty()) return ;
    myStack.pop();
}

template <typename T>
AutomaticStackManager<T>::~AutomaticStackManager() {
    s.push(ele);
}

#endif //CHAPTER_12_ERROR_HANDLING_AUTOMATICSTACKMANAGER_H
