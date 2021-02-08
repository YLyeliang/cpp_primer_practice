//
// Created by yel on 2021/2/5.
//

#include "string"
#include "vector"
#include "memory"
#include "./Sales_data.h"
//#include "chapter132.h"
#include "chapter132_ptrlike.h"

// copy control and resource management
int main() {
    // Classes that act like values, see 132.h



    // Defining classes that act like pointers      see 132_ptrlike.ph
    // The easiest way to make a class act like a pointer is to use shared_ptrs to manage the resources in the class
    // The shared_ptr class itself keep track of how many users are sharing the pointed-to object.
    // Reference count
    // Reference count works as follows:
    // 1. In addition to initializing the object, each constructor creates a counter. When create, the counter is 1.
    // 2. The copy constructor does not allocate a new counter; it copies the data members and counter, the copy
    // constructor increment the shared counter.
    // 3. The destructor decrement the shared counter. If it goes to zero, destructor delete the state
    HasPtr p1("Hiya");
    HasPtr p2(p1); // p1 and p2 point to the same string
    HasPtr p3(p1); // all ... to the same
    // if the reference count is stored in each object, how can we update it correctly when p3 is created.
    // one way is to use dynamic memory
    // defining a reference-counted class




}