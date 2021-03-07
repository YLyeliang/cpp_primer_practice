//
// Created by yel on 2021/3/7.
//

#ifndef CPP_PRIMER_PRACTICE_165_H
#define CPP_PRIMER_PRACTICE_165_H

#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"
#include "../chapter7/Sales_data.h"

using namespace std;

// it's not always possible to write a single template that is best suited for every possible template argument
// with which the template might be instantiated.
// first version: can compare any two types
template<typename T>
int compare(const T &, const T &);

// second version to handle string literals
template<size_t N, size_t M>
int compare(const char (&)[N], const char(&)[M]);
// see example 1

// Defining a function template specialization
// add empty brackets after template to specialize:
// special version of compare to handle pointers to character arrays
template<>
int compare(const char *const &p1, const char *const &p2) {
    return strcmp(p1, p2);
}
// here we are specializing the first function, in which params are references to a const Type.
// we want to define a specialization of this functino with T as const char*. Our function requires a reference to
// the const version of this type.

// Function Overloading versus template specialization
// specializations instantiate a template; they don't overload it

// Class template specializations
// as a example, we'll define a specialization of the library hash template that to store Sales_data
// specialized hash class must define
// 1. overloaded call operator, returns a size_t and takes an object of the container's key type
// 2. two type member, result_type and argument_type, which are the return and argument types, of the call operator
// 3. default constructor and copy-assignment operator

// open the std namespace so we can specialize std::hash
namespace std {
    // close the std namespace; note: no semicolon after the close curly
}
// any definitions that appear between the open and close curlies will be part of the std namespace
// open the std namespace so we can specialize std::hash
namespace std {
    template<>  // we're defining a specialization with
    struct hash<Sales_data> // the template parameter of Sales_data
    {
        // the type used to hash an unordered container must define these types
        typedef size_t result_type;
        typedef Sales_data argument_type;   // by default, this type needs ==
        size_t operator()(const Sales_data &s) const;
        // our class uses synthesized copy control and default constructor
    };

    size_t hash<Sales_data>::operator()(const Sales_data &s) const {
        return hash<string>()(s.bookNo) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
}
// see example 2

// class-template partial specializations
// a class template partial specialization is itself a template

#endif //CPP_PRIMER_PRACTICE_165_H
