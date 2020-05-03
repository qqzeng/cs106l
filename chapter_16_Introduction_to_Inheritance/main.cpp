#include <iostream>
#include "SimpleFunction.h"
#include "CompositionFunction.h"
#include "DerivativeFunction.h"

using namespace std;

/* Exercise 2.  */
void testSimpleFunction() {
    Function* funObj = new SimpleFunction([](double v) { return v * v;});
    cout << funObj->evaluateAt(5.0) << endl;
}

/* Exercise 3.  */
void testCompositionFunction() {
    Function* funObj1 = new SimpleFunction([](double v) { return v * v;});
    Function* funObj2 =  new SimpleFunction([](double v) { return v * 2;});
    Function* compFuncObj = new CompositionFunction(funObj1, funObj2);
    cout << compFuncObj->evaluateAt(5.0) << endl;
}

/* Exercise 4.  */
void testDerivativeFunction() {
    Function* funObj = new SimpleFunction([](double v) { return v * v;});
    Function* deriFuncObj = new DerivativeFunction(funObj, 0.1);
    cout << deriFuncObj->evaluateAt(5.0) << endl;
}

int main() {
//    testSimpleFunction();
//    testCompositionFunction();
    testDerivativeFunction();
    return 0;
}