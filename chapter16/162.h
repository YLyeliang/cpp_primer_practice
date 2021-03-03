//
// Created by yel on 2021/3/3.
//

#ifndef NOW_CODE_162_H
#define NOW_CODE_162_H

#include "string"
#include "memory"
#include "iostream"

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

#endif //NOW_CODE_162_H
