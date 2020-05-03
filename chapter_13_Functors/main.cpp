#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <deque>
#include <numeric>
#include <cmath>
#include <string.h>
#include <functional>
#include "NumberOperation.h"
#include "BiasedSortHelper.h"
#include "FillHelper.h"
#include "ExpungeHelper.h"
#include "DeviationHelper.h"
#include "CapAtValueHelper.h"
#include "BindOnly.h"
#include "not1_.h"

using namespace std;

/* Exercise 10. */
int MyAccumulate(vector<int>::const_iterator first, vector<int>::const_iterator last, int initVal) {
    return for_each(first, last, NumberOperation<int>(initVal)).get();
}

void testForEach() {
    vector<int> v;
    for (int i = 1; i <= 5; i++) {
        v.push_back(i);
    }
    cout << MyAccumulate(v.begin(), v.end(), 0) << endl;
}

/* Exercise 11. */
string randStr(const int length) {
    const char letters[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    char ch[length + 1] = {0};
//    srand((unsigned) time(NULL));
    for (int i = 0; i < length; ++i) {
        int x = rand() % (sizeof(letters) - 1);
        ch[i] = letters[x];
    }
    return string(ch);
}

void AdvancedBiasedSort(vector<string> &strs, const string &winner) {
    sort(strs.begin(), strs.end(), BiasedSortHelper(winner));
}

template <typename T>
void printHelper(typename vector<T>::const_iterator first, typename vector<T>::const_iterator last, char separation) {
    while (first != last) {
        cout << *first++ << separation;
    }
    cout << endl;
}

void testSort() {
    const int size = 8;
    vector<string> strs;
    const int length = 7;
    const string winner = "abcdefg";
    for (int i = 1; i <= size; i++) {
        strs.push_back(randStr(length));
    }
    strs.push_back(winner);
    strs.insert(strs.begin()+3, winner);
    cout << "before sorted: " << endl;
    printHelper<string>(strs.begin(), strs.end(), '\n');
    cout << "after sorted: " << endl;
    AdvancedBiasedSort(strs, winner);
    printHelper<string>(strs.begin(), strs.end(), '\n');
}

/* Exercise 11-1. */
template <typename T>
void printHelper2(typename deque<T>::const_iterator first, typename deque<T>::const_iterator last) {
    int flag = 0;
    while (first != last) {
        cout << string(*first) << endl;
        first++;
        flag++;
    }
    cout << flag << endl;
}

template <typename T>
void AdvancedBiasedSort2(const T &first, const T &end, const string &winner) {
    sort(first, end, BiasedSortHelper(winner));
}

void testSort2_1() {
    const int size = 8;
    vector<string> strs;
    const int length = 7;
    const string winner = "abcdefg";
    for (int i = 1; i <= size; i++) {
        strs.push_back(randStr(length));
    }
    strs.push_back(winner);
    strs.insert(strs.begin()+3, winner);
    cout << "before sorted: " << endl;
    printHelper<string>(strs.begin(), strs.end(), '\n');
    cout << "after sorted: " << endl;
    AdvancedBiasedSort2(strs.begin(), strs.end(), winner);
    printHelper<string>(strs.begin(), strs.end(), '\n');
}

void testSort2_2() {
    const int size = 8;
    deque<string> ds;
    const int length = 7;
    const string winner = "abcdefg";
    for (int i = 1; i <= size; i++) {
        ds.push_back(randStr(length));
    }
    ds.push_back(winner);
    ds.insert(ds.begin()+3, winner);
    cout << "before sorted: " << endl;
    printHelper2<string>(ds.begin(), ds.end());
    cout << "after sorted: " << endl;
    AdvancedBiasedSort2(ds.begin(), ds.end(), winner);
    printHelper2<string>(ds.begin(), ds.end());
}

void testSort2() {
    testSort2_1();
    testSort2_2();
}

/* Exercise 11-2. */
template <typename T>
bool isLessThan(const T& v1, const T& v2) {
    return v1 < v2;
}

template <typename T>
void AdvancedBiasedSort3(const T &first, const T &end) {
    sort(first, end, isLessThan<int>);
}

void testSort3() {
    const int size = 8;
    vector<int> ints;
    const string winner = "abcdefg";
    for (int i = 1; i <= size; i++) {
        ints.push_back(rand()%100);
    }
    cout << "before sorted: " << endl;
    printHelper<int>(ints.begin(), ints.end(), '\n');
    cout << "after sorted: " << endl;
    AdvancedBiasedSort3(ints.begin(), ints.end());
    printHelper<int>(ints.begin(), ints.end(), '\n');
}

/* Exercise 13. */
void FillAscending(vector<int>::iterator first, vector<int>::iterator end) {
    generate(first, end, FillHelper(0));
}

void testFill() {
    const int size = 8;
    vector<int> ints(size);
    cout << "after filled: " << endl;
    FillAscending(ints.begin(), ints.end());
    printHelper<int>(ints.begin(), ints.end(), '\n');
}

/* Exercise 14. */
template <typename T>
void ExpungeLetter(const T& first, const T& end, T begin, char ch) {
    remove_copy_if(first, end, begin, ExpungeHelper(ch));
}

void testExpunge() {
    const int size = 8;
    deque<string> ds;
    deque<string> result(size);
    const int length = 7;
    for (int i = 1; i <= size; i++) {
        ds.push_back(randStr(length));
    }
    cout << "before expunged: " << endl;
    printHelper2<string>(ds.begin(), ds.end());
    cout << "after expunged: " << endl;
    ExpungeLetter(ds.begin(), ds.end(), result.begin(), 'b');
    printHelper2<string>(result.begin(), result.end());
}

/* Exercise 15. */
template <typename T>
double StandardDeviation(const T& begin, const T& end) {
    const int numElems = distance(begin, end);
    const double average = accumulate(begin, end, 0.0) / numElems;
    double result = accumulate(begin, end, 0.0, DeviationHelper(average));
    return sqrt(result / numElems);
}

void testStandardDeviation() {
    const int size = 3;
    vector<int> ints;
    for (int i = 1; i <= size; i++) {
        ints.push_back(rand()%10);
    }
    cout << "the point is : ";
    printHelper<int>(ints.begin(), ints.end(), ' ');
    cout << "the standard deviation is : ";
    cout << StandardDeviation(ints.begin(), ints.end()) << endl;
}

/*Exercise 16. */
char* randCStr(const int length) {
    const char letters[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    char *ch = (char *)malloc(length);
//    srand((unsigned) time(NULL));
    for (int i = 0; i < length; ++i) {
        int x = rand() % (sizeof(letters) - 1);
        ch[i] = letters[x];
    }
    return ch;
}

template <typename ForwardIterator>
void ClearAllStrings(ForwardIterator first, ForwardIterator last) {
    char emptyStr[] = "";
    for_each(first, last, bind2nd(ptr_fun(strcpy), emptyStr));
}


//template <typename ForwardItr>
//void ClearAllStrings(ForwardItr begin, ForwardItr end)
//{
//    for_each(begin, end, mem_fun_ref(&string::clear));
//}

void testClearAllStrings() {
    const int size = 8;
    deque<char*> ds;
    const int length = 7;
    for (int i = 1; i <= size; i++) {
        char* tmpStr = randCStr(length);
        ds.push_back(tmpStr);
    }
    cout << "before cleared: " << endl;
    printHelper2<char*>(ds.begin(), ds.end());
    cout << "after cleared: " << endl;
    ClearAllStrings(ds.begin(), ds.end());
    printHelper2<char*>(ds.begin(), ds.end());
}



/*Exercise 17. */
string ApplyROT128(string &plainText, int accu) {
    transform(plainText.begin(), plainText.end(), plainText.begin(), bind2nd(plus<int>(), accu));
    return plainText;
}

void testApplyROT128() {
    string plainText = "abcdefg";
    cout << ApplyROT128(plainText, 128);
}

/*Exercise 18. */
template <typename ForwardIterator, typename T>
void CapAtValue(ForwardIterator first, ForwardIterator last, const T& val) {
    replace_if(first, last, CapAtValueHelper<T>(val), val);
}

void testCapAtValue() {
    vector<string> strs = {
            "abcd",
            "bcd",
            "xyz",
            "uvw",
            "opq",
            "bcd",
            "bcd"
    };
    CapAtValue(strs.begin(), strs.end(), string("bcd"));
    printHelper<string>(strs.begin(), strs.end(), '\n');
}

/*Exercise 19. */
string Concate(const string suffix) {
    return suffix + suffix;
}
void testBindOnly() {
    vector<string> strs = {
            "abcd",
            "bcd",
            "xyz",
            "uvw",
            "opq",
            "bcd",
            "bcd"
    };
    transform(strs.begin(), strs.end(), strs.begin(), BindOnly(ptr_fun(Concate), string("suffix")));
    printHelper<string>(strs.begin(), strs.end(), '\n');
}

/*Exercise 20. */
class IsPositive: public unary_function<double, bool> {
public:
    bool operator() (double value) const {
        return value > 0.0;
    }
};
void testNot1_() {
    vector<int> ints = {
            1, -2, 3, 4, 5,-2
    };
    vector<int>::iterator itr = find_if(ints.begin(), ints.end(), not1_(IsPositive()));
    cout << *itr << endl;
}
int main() {
//    testForEach();
//    testSort();
//    testSort2();
//    testSort3();
//    testFill();
//    testExpunge();
//    testStandardDeviation();
//    testClearAllStrings();
//    testApplyROT128();
//    testCapAtValue();
//    testBindOnly();
//    testNot1_();
    return 0;
}

