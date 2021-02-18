//
// Created by yel on 2021/2/18.
//

#include "string"
#include "iostream"
#include "utility"

using namespace std;

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



}