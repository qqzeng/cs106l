#include <iostream>
#include <algorithm>
#include "Grid.h"

using namespace std;

void TestGridBasic() {
    Grid<int> g1;
    cout << g1.size() << endl;

    const Grid<int> g2(10, 10);
    cout << g2.size() << endl;
    cout << g2.getAt(2, 2) << endl;

    Grid<int> g3(10, 10);
    g3.clear();
    cout << g3.size() << endl;

    g3.resize(8, 8);
    cout << g3.size() << endl;
}

void TestGridBasic2() {
    Grid<int> g1(4, 4);
    for (int i = 0; i < g1.numRows(); ++i)  {
        for (int j = 0; j < g1.numCols(); ++j) {
            g1[i][j] = rand() % 100;
            cout << g1[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < g1.numRows(); ++i)  {
        if (i >= 2) {
            sort(g1.row_begin(i), g1.row_end(i));
        } else if (i == 1) {
            fill(g1.row_begin(i), g1.row_end(i), -1);
        }
        for (Grid<int>::const_iterator itr = g1.row_begin(i); itr != g1.row_end(i); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }

    cout << endl;
    g1.resize(2, 2);
    for (int i = 0; i < g1.numRows(); ++i)  {
        for (Grid<int>::const_iterator itr = g1.row_begin(i); itr != g1.row_end(i); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
}

void TestGridBasic3() {
    Grid<int> g1(4, 4);
    Grid<int> g2(4, 4);
    cout << (g1 < g2) << " " << (g1 <= g2) << " " << (g1 > g2) << " " << (g1 >= g2) << " "
         << (g1 == g2) << " " << (g1 != g2) << endl;
    Grid<int> g3(5, 2);
    cout << (g1 < g3) << " " << (g1 <= g3) << " " << (g1 > g3) << " " << (g1 >= g3) << " "
         << (g1 == g3) << " " << (g1 != g3) << endl;
    Grid<int> g4(2, 6);
    cout << (g1 < g4) << " " << (g1 <= g4) << " " << (g1 > g4) << " " << (g1 >= g4) << " "
         << (g1 == g4) << " " << (g1 != g4) << endl;
    Grid<int> g5(4, 4);
    g1[0][0] = 0;
    g5[0][0] = 1;
    cout << (g1 < g5) << " " << (g1 <= g5) << " " << (g1 > g5) << " " << (g1 >= g5) << " "
         << (g1 == g5) << " " << (g1 != g5) << endl;

}

//void TestGridBasic4() {
//    Grid<int> g1(5, 5);
//    for (int i = 0; i < g1.numRows(); ++i)  {
//        for (int j = 0; j < g1.numCols(); ++j) {
////            g1[i][j] = rand() % 100;
////            cout << g1[i][j] << " ";
//            g1.setAt(i, j, rand() % 100);
//            cout << *(g1.row_begin(i)+j) << " ";
//        }
//        cout << endl;
//    }
//
//    cout << endl;
//    const Grid<int>::Span rows = Grid<int>::Span(1, 3);
//    const Grid<int>::Span cols = Grid<int>::Span(2, 4);
//    Grid<int> result = g1[rows][cols];
//    for (int i = 0; i < result.numRows(); ++i)  {
//        for (int j = 0; j < result.numCols(); ++j) {
//            cout << *(result.row_begin(i)+j) << " ";
//        }
//        cout << endl;
//    }
//}

int main() {
//    TestGridBasic4();
    TestGridBasic3();
//    TestGridBasic2();
//    TestGridBasic();

    return 0;
}