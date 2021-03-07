//
// Created by yel on 2021/3/3.
//
#include "string"
#include "memory"
#include "iostream"
#include "vector"
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
    int i=1;
    auto val3 = sum<long long>(i, lng); // long long sum(int, long)

    // error: can't infer initial template parameters
    auto val4 = alternative_sum<long long>(i, lng);
    // ok:
    auto val5 = alternative_sum<long long, int, long>(i, lng);

    // example 4
    compare(lng, 1024); // error: don't match
    compare<long>(lng, 1024);    // ok: compare(long,long)
    compare<int>(lng, 1024); // ok: compare(int,int)

    // example 5
    vector<int> vi = {1, 2, 3, 4, 5};
    Blob <string> ca = {"hi", "bye"};
    auto &ii = fcn(vi.begin(), vi.end()); // fcn should return int&
    auto &s = fcn(ca.begin(), ca.end());    // fcn should return string&

    // example 6
    func(compare);  // error: which instantiation of compare
    // we can disambiguate the call to func by using explicit template arguments:
    func(compare<int>);

    // example 7
    f1(i);  // template parameter T is int
    const int ci = 0;
    f1(ci); // ci is a const int; T is const int
    f1(5);  // error: argument to a & must be an lvalue

    // parameter in f2 is const &, const in the argument is irrelevant
    // in each of these three calls, f2's function parameter is inferred as const int &
    f2(i);  // T is int
    f2(ci); // ci is an const int; but T is int
    f2(5);  // a const & can be bound to a rvalue, T is int

    f3(42); // argument is an rvalue of type; template parameter T is int

    // example 8
    f3(i);  // argument is an lvalue; template parameter T is int&
    f3(ci); // ... const int &
    // when a template parameter T is deduced as a reference type, the collapsing rule says that the function parameter
    // T&& collapses to an lvalue reference type
    // The f3(i) would be something like:
    // void f3<int &>(int &T &&);   // When T is int&, function parameter is int& &&
    // Thus, even though the form of the function type in f3 is a rvalue reference, this call instantiates f3 with an
    // lvalue reference type:
    void f3<int &>(int &);    // when T is int&, function parameter collapses to int&

    // example 9
    // we can pass either an lvalue or rvalue to move
    string ss1("hi!"), ss2;
    ss2 = std::move(string("bye!")); // ok: moving from an rvalue
    ss2 = std::move(ss1);    // ok: but after the assignment ss1 has indeterminate value

    // example 10
    // f changes the value of the argument bound to v2. However, we call f through flip1, the changes made by f
    // do not affect the original argument:
    int &j = i;
    ff(42, j);   // f changes its argument j
    flip1(ff, j, 42);  // f called through flip1 leaves j unchanged
    // that is j passed to the t1, and it's a int not int&.
    // it's exactly: void flip1(void(*ff)(int,int),int t1, int2))

    flip2(g, j, 42);    // error: can't initialize int&& from lvalue


}

