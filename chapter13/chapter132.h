//
// Created by yel on 2021/2/7.
//

#ifndef NOW_CODE_CHAPTER132_H
#define NOW_CODE_CHAPTER132_H

#include "string"

using namespace std;

class HasPtr {
public:
    HasPtr(const string &s = string()) :
            ps(new string(s)), i(0) {}

    // each HasPtr has its own copy of string to which ps points
    HasPtr(HasPtr const &p) :
            ps(new string(*p.ps)), i(*p.i) {}

    HasPtr &operator=(const HasPtr &);

    ~HasPtr() { delete ps; }

private:
    string *ps;
    int i;
};

// Valuelike Copy-Assignment Operator
HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    auto newp = new string(*rhs.ps);   // copy the underlying string
    delete ps; // free the old memory
    ps = newp; // copy data from rhs into this object
    i = rhs.i;
    return *this; // return this object
}



#endif //NOW_CODE_CHAPTER132_H
