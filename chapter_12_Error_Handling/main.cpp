#include <iostream>
#include <stack>
#include "AutomaticStackManager.h"

using namespace std;

void DoSomething(stack<string> &myStack) {
    throw invalid_argument("a fake exception..");
}

void ManipulateStack(stack<string>& myStack) {
    if (myStack.empty())
        throw invalid_argument("Empty stack!");
    string &topElem = myStack.top();
    myStack.pop();
    /* This might throw an exception! */
    try {
        DoSomething(myStack);
    } catch (...) {
        myStack.push(topElem);
        throw;
    }
    myStack.push(topElem);
}

void ManipulateStack2(stack<string>& myStack) {
    if (myStack.empty())
        throw invalid_argument("Empty stack!");
    AutomaticStackManager<string> asManager(myStack);
    DoSomething(myStack);
}

void test1() {
    stack<string> myStack;
    myStack.push("abc");
    myStack.push("ABC");
    try {
        ManipulateStack2(myStack);
    } catch (...) {
        while (!myStack.empty()) {
            cout << myStack.top() << " ";
            myStack.pop();
        }
    }
}

int main() {
    test1();
    return 0;
}