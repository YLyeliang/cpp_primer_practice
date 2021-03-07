//
// Created by yel on 2021/3/7.
//

// Overloading and Templates

#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"
#include "163.h"

using namespace std;

int main() {
    // example 1
    string s("hi");
    cout << debug_rep(s) << endl;
    // for this, the first version is viable.
    // with a pointer
    cout << debug_rep(&s) << endl;
    // both functions generate viable instantiations
    // debug_rep(const string*&), with T bound to string*
    // debug_rep(string*), with T bound to string
    // The first version need to convert the plain pointer to const.
    // The second is an exact match, so the second is chosen.

    const string *sp = &s;
    cout << debug_rep(sp) << endl;
    // both are viable and exact match:
    // debug_rep(const string*&) with T bound to const string*
    // debug_rep(const string*) with T bound to const string
    // This resolves to debug_rep(T*), which is more specialized template

    // non-template and template overloads
    cout << debug_rep(s) << endl;
    // two equally good viable functions
    // debug_rep<string>(const string&)
    // debug_rep(const string&)
    // the non-template is selected.

    // overloaded templates and conversions
    cout << debug_rep("hi world") << endl;  // calls debug_rep(T*)
    // three are viable
    // debug_rep(const T&), with T bound to char[10]
    // debug_rep(T*), with T bound to const char
    // debug_rep(const string&), which requires a conversion from const char* to string
    // Both two templates provide an exact match

}
