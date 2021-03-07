//
// Created by yel on 2021/3/3.
//

#ifndef NOW_CODE_162_H
#define NOW_CODE_162_H

#include "string"
#include "memory"
#include "iostream"
#include "utility"

using namespace std;

// Template Argument Deduction

// 162.1 Conversions and template type parameters
template<typename T>
T fobj(T, T);   // arguments are copied
template<typename T>
T fref(const T &, const T &);   // references
// instantiation see example 1
// const conversions and array or function to pointer are the only automatic conversions for arguments to parameters
// with template types

// Function parameters that use the same template parameter type
// a template type parameter can be used as the type of more than one function parameter. the arguments to such params
// must have essentially the same type
// rethink the compare from 161
template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

//long lng;
//compare(lng,1024);  // error:  compare(long,int)
// The solution to this is define two different type parameters:
template<typename A, typename B>
int flexibleCompare(const A &v1, const B &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

// Normal Conversions apply for ordinary arguments
template<typename T>
ostream &print(ostream &os, const T &obj) {
    return os << obj;
}
// see example 2

// 162.2 Function-template explicit arguments
// Specifying an Explicit Template Argument
// In some cases, we want to let the user control the type. For example,
// T1 cannot be deduced: it doesn't appear in the function parameter list
template<typename T1, typename T2, typename T3>
T1 sum(T2, T3);

// The caller must provide an explicit template argument for this parameter on each call to sum.
// Instantiation see example 3
// An explicit template argument are matched from left to right, and may be omitted only for the trailing parameters,
// if sum written as
// poor design: users must explicitly specify all three template parameters
template<typename T1, typename T2, typename T3>
T3 alternative_sum(T2, T1);
// still in example 3

// Normal conversions apply for explicitly specified arguments
// see example 4

// 162.3 Trailing return types and type transformation
// requiring an explicit template argument imposes a burden on the user with no compensating advantages.
// for example, a function that takes a pair of iterator, return a reference to an element in the sequence
template<typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
    // process the range

    return *beg;    // return a reference to an element from the range
}
// instantiation see example 5
// we don't know the exact type we want to return, but we do know that type to be a reference
// we can use decltype(*beg) to obtain the type of that expression.
// To define this function, we must use a trailing return type, see above

// The type transformation library template classes
// sometimes we don't have direct access to the type that we need.
// for example, a similar function to fcn that return an element by value, rather than reference to an element
// to obtain the element type, we can use type transformation template, which defined in type_traits header
// In this case, remove_reference are used to obtain the element type.
template<typename It>
auto func2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
    // process the range
    return *beg;    // return a copy of an element from the range
}
// Note: type is member of a class that depends on a template parameter.
// As a result, we must use typename in the declaration of the return type to tell the compiler that type represents a type

// 162.4 Function Pointers and argument deduction
// pf1 points to the instantiation int compare(int&,int&)
int (*pf1)(const int &, const int &) = compare;

// It's an error if the template arguments cannot be determined from the function pointer type
// overloaded versions of func; each takes a different function pointer type
void func(int(*)(const string &, const string &));

void func(int(*)(const int &, const int &));
// see example 6

// 162.5 Template argument deduction and references
// In order to understand type deduction from a call to function such as
template<typename T>
void f(T &p);
// p is a reference to a template type parameter T, two points: Normal reference binding rules apply; const are low level

// type deduction from lvalue references function parameters
template<typename T>
void f1(T &);    // argument must be an lvalue
// calls to f1 use the referred-to type of the argument as the template parameter type, see example 7

template<typename T>
void f2(const T &);  // can take an rvalue, still see example 7

// type deduction from rvalue reference function parameters
template<typename T>
void f3(T &&);
// still see example 7

// Reference collapsing and rvalue reference parameters
// for a given type X:
// X& &, X& &&, and X&& & all collapse to type X&
// The type X&& && collapse to X& &
// Reference collapse applies only when a reference to a reference is created indirectly, such as in a type alias
// or a template parameter
// see example 8

// Writing Template functions with rvalue reference parameters
template<typename T>
void f3(T &&val) {
    T t = val;   // copy or binding a reference?
    t = fcn(t);   // does the assignment change only t or val and t?
    if (val == t) {} // always true if T is a reference type
}
// when we call f3 on a value, such as 42, T is int. local variable t has type int and is initialized by copying.

// 16.2.6 understanding std::move
// it's a good illustration of a template that uses rvalue references.
// How std::move is defined
template<typename T>
typename remove_reference<T>::type &&move(T &&t) {
    // static_cast
    return static_cast<typename remove_reference<T>::type &&>(t);
}
// see example 9

// How std::move works
// from example 9, std::move(string("bye"))
// deduced T is string;
// remove_reference is instantiated with string;
// type member of remove_reference<string> is string;
// return type of move is string&&
// move's function parameter, t, has string&&
// accordingly, that it: string&& move(string &&t)

// std::move(ss1)
// T is string&(reference to string, not plain string)
// remove_reference instantiated with string&
// type member of remove_reference<string> is string
// return type of move is string
// t instantiates as string& &&, which collapses to string&
// string&& move(string &t)

// static_cast from an lvalue to an rvalue reference is permitted

// 162.7 Forwarding
// template that takes a callable and two parameters
// and calls the given callable with the parameters "flipped"
// flip1 is an incomplete implementation: top-level const and references are lost
template<typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}

// works fine until we use it to call a function has a reference param:
void ff(int v1, int &v2) {
    cout << v1 << " " << ++v2 << endl;
}
// see example 10

// Defining Function parameters that retain type information
template<typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2) {
    f(t2, t1);
}

// if we call flip1(ff,j,42). lvalue j passed to the t1.
// In flip2, the type deduced for T1 is int&
// That is, an rvalue reference to a template parameter(i.e. T&&), preserves the constness and lvalue/rvalue property
// of its corresponding argument
// Bug flip2 cannot used to call func has rvalue reference param
void g(int &&i, int &j) {
    cout << i << " " << j << endl;
}
// still in example 10

// Using std::forward to preserve type information in a call
// like move, forward is defined in the utility header
// forward must be called with an explicit template argument, returns an rvalue reference to that explicit argumen type.
// forward<T> is T&&
template<typename Type>
void intermediary(Type &&arg) {
    finalFcn(std::forward<Type>(arg));
}

// when used with function parameter that is T&&, forward preserves all the details about an argument's type
// rewrite flip
template<typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

#endif //NOW_CODE_162_H
