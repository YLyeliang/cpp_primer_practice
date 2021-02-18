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


#endif //NOW_CODE_136_H
