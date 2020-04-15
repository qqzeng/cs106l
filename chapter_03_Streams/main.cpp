#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;


/**
 *  Some program solutions of exercises about c++ stream.
 */

// int to string
string IntToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// input a double value from standard input
double GetReal() {
    while (true) {
        string numStr;
        getline(cin, numStr);
        stringstream ss;
        ss << numStr;
        double num;
        if (ss >> num) {
            char remaining;
            if (ss >> remaining) {
                cerr << "Unexpected character: " << remaining << endl;
            } else {
                return num;
            }
        } else {
            cout << "Please enter an integer." << endl;
        }
        cout << "Retry: " << endl;
    }
}

// input a bool value from standard input
double GetBoolean() {
    while (true) {
        string numStr;
        getline(cin, numStr);
        stringstream ss;
        ss << boolalpha << numStr;
        bool boolV;
        if (ss >> boolV) {
            char remaining;
            if (ss >> remaining) {
                cerr << "Unexpected character: " << remaining << endl;
            } else {
                return boolV;
            }
        } else {
            cout << "Please enter true or false." << endl;
        }
        cout << "Retry: " << endl;
    }
}

// judge whether a number converted from decimal to hexadecimal contains a letter
bool HasHexLetters(int num) {
    stringstream ss;
    ss << hex << num;
    int decBasedNum;
    ss >> dec >> decBasedNum;
    if (ss.fail()) return true;
    else cout << decBasedNum << endl;
    char leftOverLetter;
    ss >> leftOverLetter;
    return !ss.fail();
}

// draw a triangle whose height is #height and is made up of character #c.
void DrawTriangle(int height, const char c) {
    int sNum = height - 1;
    int cNum = 0;
    for (int i = 1; i <= height; ++i) {
        cout << setfill(' ') << setw(sNum) << "";
        cNum = i * 2 - 1;
        cout << setfill(c) << setw(cNum) << "";
//        cout << setfill(' ') << setw(sNum) << "";
        cout << endl;
        sNum--;
    }
}

// open a file by given its input file stream and return it if it indeed exists
void OpenFile(ifstream &myStream) {
    cout << "The open file name: " << endl;
    string fileName;
    while (true) {
        cin >> fileName;
        myStream.open(fileName);
        if (!myStream.is_open()) {
            cerr << "Couldn't open the file: " << fileName << endl;
            myStream.clear();
        } else {
            return;
        }
    }
}

void ReadFile() {
    ifstream myStream;
    OpenFile(myStream);
    string line;
    while (getline(myStream, line)) {
        cout << line << endl;
    }
}

int main() {
    cout << boolalpha << HasHexLetters(4273); // 0x10B1
//    cout << boolalpha << GetBoolean() << endl;
//    cout << IntToString(343) << endl;
//    cout << GetReal() << endl;
//    ReadFile();
//    DrawTriangle(10, '#');
    return 0;
}