//
// Created by fiberhome on 2021/1/26.
//

#ifndef NOW_CODE_STRBLOB_H
#define NOW_CODE_STRBLOB_H

#include "vector"
#include "string"
#include "memory"
#include "StrBlobPtr.h"

using namespace std;

// we'll implement a small subset of vector operations. We'll also change the operations that access elements
// ( e.g. front back)
class StrBlob {
public:
    typedef std::vector<std::string>::size_type size_type;

    friend class StrBlobPtr;

    StrBlobPtr begin() { return StrBlobPtr(*this); }

    StrBlobPtr end() {
        auto ret = StrBlobPtr(*this, data->size());
        return ret;
    }

    StrBlob();

    StrBlob(std::initializer_list<std::string> il);

    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }

    void pop_back();

    //element access
    std::string &front();

    std::string &back();

private:
    std::shared_ptr<std::vector<std::string>> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// constructors
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il) :
        data(std::make_shared<std::vector<std::string>>(il)) {}

// Element Access Members
void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

// The front and back members should be overloaded on const
string &StrBlob::front() {
    // if the vector is empty, chekc will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    return data->pop_back();
}

// copying, assigning, and destroying StrBlobs
// has only one data member, which is a shared_ptr
// Therefore, when we copy, assign, or destroy a StrBlob, its
// shared_ptr member will be copied, assigned, or destroyed




#endif //NOW_CODE_STRBLOB_H


