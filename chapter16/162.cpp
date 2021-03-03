//
// Created by yel on 2021/3/3.
//
#include "string"
#include "memory"
#include "iostream"
#include "./162.h"
#include "fstream"

using namespace std;

// Template Argument Deduction

int main() {
    // example 1
    string s1("a value");
    const string s2("another value");
    fobj(s1, s2);    // calls fobj(string, string) ; const is ignored
    fref(s1, s2);    // calls fref(const string&, const string&), uses premissible conversion to const on s1

    int a[10], b[42];
    fobj(a, b);  // calls f(int*,int*)
    fref(a, b);  // error: array types don't match  int& don't match
    // In first fobj, the arguments are copied, so whether the original object is const doesn't matter.
    // The first fref, parameter type is a reference to const. It's legal
    // In second fobj, the arrays are different sizes and hence have different types, both converted to pointers

    // example 2
    print(cout, 42); // instantiates print (ostream&, int)
    ofstream f("output");
    print(f, 10);    // uses print(ostream&,int); converts f to ostream&

    // example 3
    long lng;
    int i;
    auto val3 = sum<long long>(i, lng); // long long sum(int, long)

    // error: can't infer initial template parameters
    auto val4 = alternative_sum<long long>(i, lng);
    // ok:
    auto val5 = alternative_sum<long long, int, long>(i, lng);

    // example 4
    compare(lng,1024); // error: don't match
    compare<long>(lng,1024);    // ok: compare(long,long)
    compare<int>(lng,1024); // ok: compare(int,int)

}

