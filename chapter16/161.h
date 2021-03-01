//
// Created by yel on 2021/3/1.
//

#ifndef CPP_PRIMER_PRACTICE_161_H
#define CPP_PRIMER_PRACTICE_161_H

#include "string"

using namespace std;

template<typename>
class BlobPtr;

template<typename>
class Blob; // needed for parameters in operator==

template<typename T>
bool operator==(const Blob<T> &, cosnt Blob<T> &);

template<typename T>
class Blob {
    // each instantiation of Blob grants access to the version of
    // BlobPtr and the equality operator instantiated with the same type
    friend class BlobPtr<T>;

    friend bool operator==<T>
            (const Blob<T> &, const Blob<T> &);
    // other members as in 121
};
// The friend declarations uses Blob's template parameter as their own template argument.
// Thus, the friendship is restricted to those instantiation with the same type
// Blob<char> ca;   // BlobPtr<char> and operator==<char> are friends



#endif //CPP_PRIMER_PRACTICE_161_H
