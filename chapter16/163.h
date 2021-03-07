//
// Created by yel on 2021/3/7.
//

#ifndef CPP_PRIMER_PRACTICE_163_H
#define CPP_PRIMER_PRACTICE_163_H

#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"

using namespace std;
// Function templates can be overloaded by other templates or by ordinary, non-template functions

// Writing overloaded templates
// print any type we don't otherwise handle
template<typename T>
string debug_rep(const T &t) {
    ostringstream ret;
    ret << t;   // uses T's output operator to print a representation of t
    return ret.str();   // return a copy of the string to which the return bound.
}

// This func used to generate a string corresponding to an object of any type that has an output operator
// next
// print pointers as their pointer value, followed by the object to which the pointer points
// NB: this function will not work properly with char*
template<typename T>
string debug_rep(T &p) {
    ostringstream ret;
    ret << "pointer: " << p;    // print the pointer's own value
    if (p)
        ret << " " << debug_rep(*p);   // print he value to which p points
    else
        ret << " null pointer";
    return ret.str();   // ...
}
// we might use these functions as example 1

// multiple viable templates
// still in example 1

// Non-template and template overloads
string debug_rep(const string &s) {
    return '"' + s + '"';
}
// still in example 1

// overloaded templates and conversions
// example 1
// if we want to handle character pointers as strings, we can define two more non-template overloads
// convert the character pointers to string
string debug_rep(char *p) {
    return debug_rep(string(p));
}

string debug_rep(const char *p) {
    return debug_rep(string(p));
}

// Missing Declarations can cause the program to misbehave



#endif //CPP_PRIMER_PRACTICE_163_H
