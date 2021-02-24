//
// Created by yel on 2021/2/24.
//
#include "string"
#include "iostream"

using namespace std;
// Constructors and Copy Control

// Virtual Destructors
// The primary direct impact that inheritance has on copy control for a base class is that
// base class generally should define a virtual destructor.
// The destructor needs to be virtual to allow objects in the inheritance hierarchy to be dynamically allocated
// destructor is run when we delete a pointer to a dynamically allocated object
// If that pointer points to a type in an inheritance hierarchy, it is possible that the static type of the pointer
// might differ from the dynamic type of the object being destroyed.
// Thus, we arrange to run the proper destructor by defining the destructor as virtual in the base class
class Quote {
public:
    // virtual destructor is needed if a base pointer pointing to a derived object is deleted
    virtual ~Quote() = default;   // dynamic binding for the destructor
};

class Bulk_Quote : public Quote {
};

// Synthesized Copy control and Inheritance



int main() {
    Quote *itemP = new Quote;   // same static and dynamic type
    delete itemP;   // destructor for Quote called
    itemP = new Bulk_Quote;   // static and dynamic differ
    delete itemP;   // destructor for Bulk_Quote called

}