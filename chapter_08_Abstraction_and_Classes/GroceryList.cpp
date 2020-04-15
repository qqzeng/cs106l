//
// Created by GEORGE-pc on 2020/3/17.
//

#include <cstring>
#include "GroceryList.h"

void GroceryList::addItem(string quantity, string item) {
    groceries[item] = quantity;
}

void GroceryList::removeItem(string item) {
    groceries.erase(item);
}

string GroceryList::itemQuantity(string item) {
    if (itemExists(item)) {
        return groceries[item];
    } else {
        return "";
    }
}

bool GroceryList::itemExists(string item) {
    return strcmp(groceries[item].c_str(), "") != 0;
}

GroceryList::GroceryList() {

}



