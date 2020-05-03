#include <iostream>
#include "Vector.h"
#include "Singleton.h"
#include "PseudoUncopyable.h"
#include "SmartPointer.h"

void TestVector() {
    using namespace tz;
    Vector<int> v1;
    Vector<int> v2 = v1;

    std::cout << std::endl;
    Vector<int> v3(20);
    v3 = v1;

    std::cout << std::endl;
    Vector<int> v4(v1);

    std::cout << std::endl;
}

void TestSingleton0() {
    using namespace Singleton_V0;
//    printf("%d\n", Singleton::getInstance());
//    printf("%d\n", Singleton::getInstance());
}

void TestSingleton1() {
    using namespace Singleton_V1;
    printf("%d\n", Singleton::getInstance());
    printf("%d\n", Singleton::getInstance());
    Singleton* other = Singleton::getInstance();
    printf("%d\n", other);
}

void TestSingleton2() {
    using namespace Singleton_V2;
    printf("%d\n", Singleton::getInstance());
    printf("%d\n", Singleton::getInstance());
    Singleton* other = Singleton::getInstance();
    printf("%d\n", other);
}

void TestSingleton3() {
    using namespace Singleton_V3;
    Singleton *pSingleton1 = Singleton::getInstance();
    std::cout << pSingleton1 << std::endl;
    Singleton *pSingleton2 = Singleton::getInstance();
    std::cout << (pSingleton1 == pSingleton2) << std::endl;
    std::cout << Singleton::releaseInstance() << std::endl;
    std::cout << Singleton::releaseInstance() << std::endl;
}

void TestSingleton4() {
    using namespace Singleton_V4;
//    printf("%d\n", Singleton::getInstance());
//    printf("%d\n", Singleton::getInstance());
}

/* Exercise 16. */
void TestDisableCopyConstructor() {
    using namespace tz;
    Vector<int> v1;
    Vector<int> v2 = v1;

    std::cout << std::endl;
}

/* Exercise 17. */
void TestDisableCopyConstrucorExplict() {
    PseudoUncopyable pu1;
    PseudoUncopyable pu2 = pu1;
}


/* SmartPointer based on reference counting. */
void TestSmartPointer() {
    using namespace std;
    SmartPointer<string> myPtr(new string);
    *myPtr = "This is a string!";
    cout << *myPtr << endl;
    cout << myPtr.get() << endl;
    {
        SmartPointer<string> other = myPtr;
        cout << *other << endl;
        cout << other->length() << endl;
        cout << myPtr.getShareCount() << endl;
    }
    cout << myPtr.getShareCount() << endl;
    cout << *myPtr << endl;
    SmartPointer<string> myPtr2(new string);
    *myPtr2 = "This is another string";
    myPtr = myPtr2;
    cout << *myPtr << endl;
    cout << myPtr.getShareCount() << endl;
    string *s = new string("This is the third string");
    myPtr.reset(s);
    cout << *myPtr << endl;

}


int main() {
    TestSmartPointer();
//    TestDisableCopyConstructor();
//    TestSingleton4();
//    TestSingleton3();
//    TestSingleton2();
//    TestSingleton1();
//    TestSingleton0();
//    TestVector();
    return 0;
}