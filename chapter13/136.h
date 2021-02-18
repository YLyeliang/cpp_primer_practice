//
// Created by yel on 2021/2/18.
//

#ifndef NOW_CODE_136_H
#define NOW_CODE_136_H

#include "utility"
#include "string"

using namespace std;


// The Synthesized Move operations
// synthesizes the move constructor and assignment only if a class does not define any of its own copy-control
// and only if all the data members can be moved constructed and assigned, respectively.

// the compiler will synthesize the move operations for X and hasX
struct X {
    int i;  // built-in type can be moved
    string s;   // string defines its own move operations
};
struct hasX {
    X mem;  // X has synthesized move operations
};
X x, x2 = std::move(x); // uses the synthesized move constructor
hasX hx, hx2 = std::move(hx); // uses the synthesized move constructor

// Classes that define a move constructor or move-assignment operator must also define their own copy operations.
// Otherwise, those members are deleted by default

// assume Y is a class that defines its own copy constructor but not a move constructor
struct hasY {
    hasY() = default;

    hasY(hasY &&) = default;

    Y mem;  // hasY will have a deleted move constructor
};

hasY hy, hy2 = std::move(hy);   // error: move constructor is deleted



#endif //NOW_CODE_136_H
