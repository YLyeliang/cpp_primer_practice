//
// Created by yel on 2021/2/28.
//
#include <vector>
#include "string"
#include "iostream"

using namespace std;
// Defining a Template

// Imagine that we want to write a compare function. We may define several such functions, each of which will compare
// values of  a given type.
// int compare(string,string)       int compare(double,double)

// Function Templates
// Rather than defining a new function for each type, we can define a function template.
// The template version of compare looks like
template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

// A template definition starts with the keyword template followed by a template parameter list,
// which is a comma-separated list of one or more template parameters bracketed by the < and > tokens

// Instantiating a Function Template
// When we call a function template, the compiler uses the arguments of the call to deduce the template arguments for us.
// see example 1

// Template Type Parameters
// ok: same type used for the return type and parameter
template<typename T>
T foo(T *p) {
    T tmp = *p;  // tmp will have the type to which p points
    // ...
    return tmp;
}

// error: must precede U with either typename or class
template<typename T, U>
calc(const T &, const U &);

// ok: ok: no distinction between typename and class in a template parameter list
template<typename T, class U>
c2(const T &, const U &);

// Nontype Template Parameters
// A nontype parameter represents a value rather than a type.
template<unsigned N, unsigned M>
int compare2(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
}
// see example 2

// inline and constexpr function templates
// ok: inline specifier follows the template parameter list
template<typename T>
inline T min(const T &, const T &);
// error: incorrect placement of the inline specifier
// inline template<typename T>
// T min(const T&,const T&);

// writing Type-independent code
// The compare function illustrates two important principles for writing generic code
// 1. The function parameters in template are reference to const
// 2. The tests in the body use only < comparisons





int main() {
    // example 1
    cout << compare(1, 0) << endl;   // T is int
    vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
    cout << compare(vec1, vec2) << endl; // T is vector<int>

    // example 2
    compare2("hi", "mom");
    // will use the size of the literals to instantiate. Which will instantiate int compare(const char (&p1)[3], const char (&p2)[4])

}


