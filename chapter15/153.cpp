//
// Created by yel on 2021/2/22.
//
#include "iostream"
#include "string"
#include "152.h"

using namespace std;

// Virtual Functions

// Calls to Virtual Functions may be resolved at run time

// the key idea behind oop is polymorphism(多态), which is derived from a Greek word meaning "many forms".

// compiler will reject a program if a function marked override does not override an existing virtual function
struct B {
    virtual void f1(int) const;

    virtual void f2();

    void f3();
};

struct D1 : B {
    void f1(int) const override;    // ok: f1 matches f1 in the base
    void f2(int) override;  // error: B has no f2(int) function
    void f3() override; // error: f3 not virtual
    void f4() override; // error: B doesn't have a function named f4
};

// we can also designate a function as final. any attempt to override it will be flagged as an error
struct D2 : B {
    // inherits f2() and f3() from B and overrides f1(int)
    void f1(int) const final;   // subsequent classes can't override f1(int)
};

struct D3 : D2 {
    void f2();  // ok
    void f1(int) const; // error: D2 declared f2 as final
};

// Virtual Functions and Default Arguments
// virtual functino can have default arguments

// Circumventing the Virtual Mechanism
// In some cases, we want to prevent dynamic binding of a call to a virtual function
// we want to force the call to use a particular version of that virtual.
// We can use the scope operator. For example
// calls the version from the base class regardless of the dynamic type of baseP
Bulk_quote *baseP;
double undiscounted = baseP->Quote::net_price(42);

int main() {
    // rethink the print_total in 151.cpp, dynamic binding happens only when a virtual function
    // is called through a pointer or a reference
    Quote base("0", 50);
    Bulk_quote derived("1", 50, 5, .19);
    base = derived; // copies the Quote part of derived into base
    base.net_price(20); // calls Quote::net_price


}
