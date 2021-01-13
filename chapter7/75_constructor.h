//
// Created by fiberhome on 2020/12/22.
//

#ifndef NOW_CODE_75_CONSTRUCTOR_H
#define NOW_CODE_75_CONSTRUCTOR_H

#include "string"

class NoDefault {
public:
    NoDefault(const std::string &);
};

struct A {
    NoDefault my_mem;
};
A a; //  error: because my_mem has no default constructor.
struct B {
    B() {};  // must explicitly initialize b_member, since it has no default constructor.
    NoDefault b_member;
};

// Aggregate class
// a class is an aggregate if
// all of its data members are public
// doesn't define any constructors
// has no in-class initializers
// no base class or virtual functions,
struct Aggregate_data {
    int ival;
    std::string s;
};
// initialize
Aggregate_data val1 = {0, "Anna"}; // must be in order.

// constexpr constructor
// A constexpr constructor must initialize every data member. The initializers
//must either use a constexpr constructor or be a constant expression
class Debug {
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}

    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}

    constexpr bool any() { return hw || io || other; }

    void set_io(bool b) { io = b; }

    void set_hw(bool b) { hw = b; }

    void set_other(bool b) { other = b; }

private:
    bool hw;
    bool io;
    bool other;
};


#endif //NOW_CODE_75_CONSTRUCTOR_H
