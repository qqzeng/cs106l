#include <iostream>
#include "GroceryList.h"

void TestGroceryList() {
    GroceryList gl;
    gl.addItem("1 gallon", "Milk");
    gl.addItem("2 gallon", "Orange Juice");
    gl.addItem("0.5 gallon", "Coffee");
    cout << boolalpha << gl.itemExists("Milk") << endl;
    cout << gl.itemQuantity("Milk")<< endl;
    gl.removeItem("Orange Juice");
    cout << boolalpha << gl.itemExists("Orange Juice") << endl;
    gl.removeItem("Milk1");
}


int main() {
    TestGroceryList();
    return 0;
}