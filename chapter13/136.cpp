//
// Created by yel on 2021/2/18.
//

#include "string"
#include "iostream"
#include "utility"
#include "135.h"

using namespace std;

class Foo {
public:
    Foo &operator=(const Foo &) &;   // may assign only to modifiable lvalues
    Foo() = default;

    Foo(const Foo &); // copy constructor
    // other members, but Foo does not define a move constructor
};

Foo &Foo::operator=(const Foo &rhs) &{
    // do whatever is needed to assign rhs to this object
    return *this;
}


// Moving objects

// the Strvec in 13.5 is a good example of superfluous copy.
// there's no need to copy, rather than move- the elements from the old memory to the new.
// A second reason to move rather than copy occurs in classes such as IO or unique_ptr, these can't be copied but
// can be moved

int main() {
    // To support move operations, the new standard introduced a new kind of reference, an rvalue reference.
    // An rvalue reference must be bound to an rvalue. using && rather than &.
    // Recall the lvalue and rvalue. Generally speaking, an lvalue expression refers to object's identity, rvalue
    // refers to object's value
    int i = 42;
    int &r = i; // ok: r refers to i
    int &&rr = i;   // error: cannot bind an rvalue reference to an lvalue
    int &r2 = i * 42; // error: i*42 is an rvalue
    const int &r3 = i * 42; // ok: we can bind a reference to const to an rvalue
    int &&rr2 = i * 42; // ok: bind rr2 to the result of multiplication

    // lvalue persist; rvalues are ephemeral

    // Variables are lvalues
    // we cannot bind an rvalue reference to a variable defined as an rvalue reference type
    int &&rr1 = 42; // ok: literals are rvalues
    int &&rr22 = rr1;    // error: the expression rr1 is an lvalue!

    // The move function
    // the move function uses facilities to return an rvalue reference to its given object
    int &&rr3 = std::move(rr1);  // ok  must specify std::move rather than move

    // move constructor and move assignment
    // see 135.h

    // The Synthesized Move operations
    // see 136.h

    // Rvalues are moved, Lvalues are copied...
    StrVec v1, v2;
    v1 = v2; // v2 is an lvalue; copy assignment
    StrVec getVec(istream &);    // getVec returns an rvalue
    v2 = getVec(cin);   // getVec(cin) is an rvalue; move assignment

    // ... But rvalues are copied if there is no move constructor
    // defined Foo()
    Foo x;
    Foo y(x);   // copy constructor; x is an lvalue
    Foo z(std::move(x));    // copy constructor, because there is no move constructor
    // The call to move(x) returns a Foo&& bound to x, we can convert a Foo&& to a const Foo&. Thus, copy are used.

    // Copy-and-Swap Assignment operators and Move
    // The class in 132_ptrlike.h is a good illustration of the interaction between function matching and move operations
    // add a move constructor to this class, it will effectively get a move assignment operator as well

    // Move operations for the Message class
    // see 134.h

    // Move Iterators
    // make_move_iterator: takes an iterator and returns a move iterator

    // 136.3 Rvalue references and member functions
    // assuming X is the element type
    void push_back(const X &);  // copy: binds to any kind of X
    void push_back(X &&);   // move: binds only to modifiable rvalues fof type X

    // Overloaded functions that distinguish between moving and copying a parameter typically have one version that
    // take a const T& and one that takes a T&&
    // see 135.h

    // Rvalue and Lvalue reference member functions
    // Ordinarily, we can call a member function on an object, regardless l- rvalue.
    string s1 = "a", s2 = "b";
    auto n = (s1 + s2).find('a');
    // see Foo()

    // Overloading and Reference Functions


}