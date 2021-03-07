//
// Created by yel on 2021/3/7.
//
#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"
#include "164.h"

using namespace std;

// Variadic Templates

int main() {
    // example 1
    int i = 0;
    double d = 3.14;
    string s = "test";
    foo(i, s, 42, d);  // three params in the pack
    foo(s, 42, "Hi"); // two
    foo(d, s);   // one
    foo("hi");  // empty pack

    // example 2
    errorMsg(cerr, "heh", "haha", "other");

    // example 3
    StrVec svec;
    svec.emplace_back(10, 'c');  // adds c*10 as a new last element
    // the pattern in the call to construct will expand to
    // std::forward<int>(10), std::forward<char>(c)
    string s1 = "a", s2 = "b";
    svec.emplace_back(s1 + s2); // the argument is an rvalue, which is passed to construct as
    // std::forward<string>(string("ab")




}