#include <iostream>

using namespace std;

#include "UniquelyIdentified.h"
#include "RationalNumber.h"
#include "RealNumber.h"
#include "RandomGenerator.h"

/* Exercise 26. */
void TestUniquelyIdentified() {
    UniquelyIdentified ui1;
    cout << ui1.getUniqueID() << endl;
    UniquelyIdentified ui2;
    cout << ui2.getUniqueID() << endl;
    UniquelyIdentified ui3;
    cout << ui3.getUniqueID() << endl;
}

/* Exercise 27. */
void TestRealRationalNumberConversion() {
    RationalNumber rn1 = 3;
    RealNumber rn2 = rn1;
    cout << rn1.getValue() << " == " << rn2.getValue() << endl;
}

void TestRandomGenerator() {
    RandomGenerator rg;
    cout << rg.next() << endl;

    RandomGenerator rg2;
    cout << rg2.next() << endl;

    RandomGenerator rg3;
    cout << rg3.next() << endl;
}

RationalNumber TestCopyEntry(RationalNumber &rn1) {
    RationalNumber rn2 = rn1;
    rn2.setNumerator(10);
    rn1.setNumerator(100);
    return rn2;
}

void TestCopy() {
    RationalNumber rn1 = 3;
    RationalNumber rn2 = TestCopyEntry(rn1);
    cout << rn1.getValue() << " " << rn2.getValue() << endl;
}


int main() {
//    TestCopy();
//    TestRandomGenerator();
//    TestRealRationalNumberConversion();
//    TestUniquelyIdentified();
    return 0;
}