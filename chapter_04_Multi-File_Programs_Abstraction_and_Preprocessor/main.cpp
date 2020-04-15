#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

/**
 * Some programs solutions of exercises about c++ preprocessor.
 */

enum Color {
#define DEFINE_COLOR(color, opposite) color, // Name followed by comma
#include "color.h"
#undef DEFINE_COLOR
    NOT_A_COLOR
};

// convert a enum to its opposite enum value
Color GetOppositeColor(Color c) {
    switch(c) {
#define DEFINE_COLOR(color, opposite) case color: return opposite;
#include "color.h"
#undef DEFINE_COLOR
        default: return c; // Unknown color, undefined result.
    }
}

// convert a enum to its corresponding string value
const char* GetStringValueFromColor(Color c) {
    switch(c) {
#define DEFINE_COLOR(color, opposite) case color: return #color;
#include "color.h"
#undef DEFINE_COLOR
        default: return "NOT_A_COLOR"; // Unknown color, undefined result.
    }
}


// Exercise-9.
static const char *strColor[] = {
#define DEFINE_COLOR(color, opposite) #color,
#include "color.h"
#undef DEFINE_COLOR
};

// convert a string value to its corresponding enum value
Color GetColorFromStrName(const char* c) {
    const int n = sizeof(strColor) / sizeof(strColor[0]);
    for (int i = 0; i < n; ++i) {
        if (strcmp(strColor[i], c) == 0)
            return (Color) i;
    }
    return Color::NOT_A_COLOR; // if not exists, return NOT_A_COLOR
}


// Exercise-10.
#define  tailored_type(x) eColor_##x
enum Color_Tailored {
#define DEFINE_COLOR(color, opposite) tailored_type(color), // Name followed by comma
#include "color.h"
#undef DEFINE_COLOR
    eColor_NOT_A_COLOR
};


// Exercise-11. Test case
const char* GetStringValueFromColorTest(Color c) {
    switch(c) {
#define DEFINE_COLOR(color, opposite) case color: return #color;
#include "color.h"
#undef DEFINE_COLOR
        default: return "NOT_A_COLOR"; // Unknown color, undefined result.
    }
}


// Exercise-12.
#define  tailored_type_unit(x)  eLengthUnit_##x

// Exercise-12(a)
enum LengthUnit {
#define DEFINE_UNIT(unitName, meters, suffix, system) tailored_type_unit(suffix),
#include "units.h"
#undef DEFINE_UNIT
    eLengthUnit_ERROR
};
// Exercise-12(b)
static const char *strUnit[] = {
#define DEFINE_UNIT(unitName, meters, suffix, system) #suffix,
#include "units.h"
#undef DEFINE_UNIT
};
// Exercise-12(c)
LengthUnit GetSuffixStringToLengthUnit(const char * unitStr) {
    const int n = sizeof(strUnit) / sizeof(strUnit[0]);
    for (int i = 0; i < n; ++i) {
        if (strcmp(strUnit[i], unitStr) == 0)
            return (LengthUnit) i;
    }
    return LengthUnit::eLengthUnit_ERROR;
}

struct Length{
    double amount;
    enum LengthUnit lu;
};
// Exercise-12(d)
Length ReadLength() {
    while (true) {
        cout << "Please input amount(double) and suffix(string): " << endl;
        string content;
        getline(cin, content);
        stringstream ss;
        ss << content;
        double amount;
        ss >> amount;
        if (ss.fail()) {
            cout << "Error input amount!" << endl;
            continue;
        }
        string suffix;
        ss >> suffix;
        if (ss.fail()) {
            cout << "Error input suffix!" << endl;
            continue;
        }
        int lengthUnit = GetSuffixStringToLengthUnit(suffix.c_str());
        if (lengthUnit == LengthUnit::eLengthUnit_ERROR) {
            cout << "Error input suffix!" << endl;
            continue;
        }
        cout << "readLength() call successfully!" << endl;
        Length length;
        length.amount = amount;
        length.lu = (LengthUnit)lengthUnit;
        return length;
    }
}

// Exercise-12(e)
const char* GetUnitType() {
    Length length = ReadLength();
    switch(length.lu) {
#define DEFINE_UNIT(unitName, meters, suffix, system) case tailored_type_unit(suffix): return #system;
#include "units.h"
#undef DEFINE_UNIT
        default: return "eLengthUnit_ERROR";
    }
}

// Exercise-12(f)
void PrintLength() {
    Length length = ReadLength();
    ostringstream osslength;
    switch(length.lu) {
#define DEFINE_UNIT(unitName, meters, suffix, system) case tailored_type_unit(suffix): \
        osslength << meters << strUnit[length.lu] << " (" << meters << " " << #unitName << ")"; break;
#include "units.h"
#undef DEFINE_UNIT
        default: cout<< "eLengthUnit_ERROR" << endl;
    }
    cout << osslength.str() << endl;
}

// Exercise-12(g)
double ConvertToMeters() {
    Length length = ReadLength();
    double totalMi;
    switch(length.lu) {
#define DEFINE_UNIT(unitName, meters, suffix, system) case tailored_type_unit(suffix): totalMi = meters * length.amount; break;
#include "units.h"
#undef DEFINE_UNIT
        default: cout<< "eLengthUnit_ERROR" << endl;
    }
    return totalMi;
}

int main() {
    cout << ConvertToMeters() << endl;
//    printLength();
//    cout << GetUnitType() << endl;
//    ReadLength();
//    cout << SuffixStringToLengthUnit("cubit") << endl;
//    cout << GetStringValueFromColorTest(Color::Red) << endl;
//    cout << Color_Tailored::eColor_Blue << endl;
//    cout << GetColorFromStrName("Cyan") << endl;
//    cout << GetOppositeColor(Color::Red) << endl;
    return 0;
}