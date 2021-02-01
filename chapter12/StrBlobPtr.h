//
// Created by fiberhome on 2021/1/30.
//

#ifndef NOW_CODE_STRBLOBPTR_H
#define NOW_CODE_STRBLOBPTR_H

#include "memory"
#include "string"
#include "vector"
#include "StrBlob.h"

using namespace std;

// class will have 2 data member: wptr, which is either null or points to a vector in a StrBlobPtr;
// curr, which is the index of the element that the object currently denotes.
class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) {}

    // to use the data member of StrBlob, our class have to be a friend of StrBlob, which defined in StrBlob

    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string &deref() const;

    StrBlobPtr &incr(); // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    shared_ptr<vector<string>> check(size_t, const string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    weak_ptr<vector<string>> wptr;
    size_t curr;  // current position within the array

};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock(); // is the vector still around?
    if (!ret)
        throw runtime_error("Unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

// pointer operations
string &StrBlobPtr::deref() const {
    auto p = check(curr, "deference past end");
    return (*p)[curr]; // (*p) is the vector to which this object points
}

// prefix: return a reference to the incremented object
StrBlobPtr &StrBlobPtr::incr() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past the end of StrBlobPtr");
    ++curr; // advance the current state
    return *this;
}


#endif //NOW_CODE_STRBLOBPTR_H
