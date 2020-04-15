//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_08_ABSTRACTION_AND_CLASSES_GROCERYLIST_H
#define CHAPTER_08_ABSTRACTION_AND_CLASSES_GROCERYLIST_H

#include <string>
#include <map>

using namespace std;

class GroceryList {
public:
    GroceryList();

    void addItem(string quantity, string item);

    void removeItem(string item);

    string itemQuantity(string item);

    bool itemExists(string item);

private:
    map<string, string> groceries;
};

#endif //CHAPTER_08_ABSTRACTION_AND_CLASSES_GROCERYLIST_H
