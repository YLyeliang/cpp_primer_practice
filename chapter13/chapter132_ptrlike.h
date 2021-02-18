//
// Created by yel on 2021/2/7.
//

#ifndef NOW_CODE_CHAPTER132_PTRLIKE_H
#define NOW_CODE_CHAPTER132_PTRLIKE_H

#include "string"


using namespace std;

class HasPtr {
public:
    // add move constructor
    HasPtr(HasPtr &&p) noexcept: ps(p.ps), i(p.i), { p.ps = 0; }

    // assignment operator is both the move- and copy-assignment operator
    HasPtr &operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
    }

    // constructor allocate a new string and a new counter, which it set to 1
    HasPtr(const string &s = string()) :
            ps(new string(s)), i(0), use(new size_t(1)) {}

    // copy constructor copies all three members and increments the counter
    HasPtr(const HasPtr &p) :
            ps(p.ps), i(p.i), use(p.use) { ++*use; }

    HasPtr &operator=(const HasPtr &);

    HasPtr &operator=(HasPtr);

    ~HasPtr();


private:
    string *ps;
    int i;
    size_t *use;    // member to keep track of how many objects share *ps

    friend void swap(HasPtr &, HasPtr &);

    inline void swap(HasPtr &lhs, HasPtr &rhs) {
        using std::swap;
        swap(lhs.ps, rhs.ps);    // swap the pointer, not the string data
        swap(lhs.i, rhs.i);  // swap the members

    }

};

// The destructor can't unconditionally delete ps -  there might be other objects pointing to that memory.
// Instead, decrements the counter and ..
HasPtr::~HasPtr() {
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

HasPtr &HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use; // increment the use count of right-hand operand
    if (--*use == 0) { // then decrement this object's counter
        delete ps;  // if no other users
        delete use; // free this object's allocated members
    }
    ps = rhs.ps;     // copy data from rhs into this object
    i = rhs.i;
    use = rhs.use;
    return *this;   // return this object
}

HasPtr &HasPtr::operator=(HasPtr rhs) {
    // swap the contents of the left-hand operand with the local variable rhs
    swap(*this, rhs);   // rhs now points to the memory this object had used
    return *this;   // rhs is destroyed, which deletes the pointer in rhs
}

#endif //NOW_CODE_CHAPTER132_PTRLIKE_H
