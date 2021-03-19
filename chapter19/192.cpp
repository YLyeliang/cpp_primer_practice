//
// Created by fiberhome on 2021/3/19.
//

#include "string"
#include "iostream"

using namespace std;
// Run-time type Identification

class Base {
    virtual const int f();
};

class Derived : public Base {
};

// example 1
void f(const Base &b) {
    try {
        const Derived &d = dynamic_cast<const Derived &>(b);
// use the Derived object to which b referred
    } catch (bad_cast) {
// handle the fact that the cast failed
    }
}

int main() {
    // RTTI is provided through two operators:
    // typeid operator, which returns the type of a given expression
    // dynamic_cast operator, which safely converts a pointer or reference to a base type into a pointer or reference
    // to a derived type

    // 192.1 The dynamic_cast operator
    // following type:
//    dynamic_cast<type*>(e)
//    dynamic_cast<type&>(e)
//    dynamic_cast<type&&>(e)
    // type must be a class type

    // pointer-type dynamic_casts
    // assume Base is a class with at least one virtual function and that Derived is publicly derived from Base.
    // If we have a pointer to Base named bp, we can cast it, at run time, to a pointer to Derived:
    Base *bpp = new Base;
    if (Derived *dp = dynamic_cast<Derived *>(bpp)) {
        // use the Derived object to which dp points
    } else { // bp points at a Base object
        // use the Base object to which bp points
    }

    // Reference-type dynamic_casts
    // rewrite the previous example to use reference as follows:
    // see example 1


    // 192.2 The typeid operator
    // allows a program to ask of an expression: what type is your object?
    // form: typeid(e), where e is any expression or a type name
    // result is a reference to const object of a library function named type_info, or a type publicly derived from type_info.

    // using the typeid operator
    Derived *dp = new Derived;
    Base *bp = dp; // both pointers point to a Derived object
    // compare the type of two objects at run time
    if (typeid(*bp) == typeid(*dp)) {
        // bp and dp point to objects of the same type
    }
    // test whether the run-time type is a specific type
    if (typeid(*bp) == typeid(Derived)) {
        // bp actually points to a Derived
    }

    // test always fails: the type of bp is pointer to Base
    if (typeid(bp) == typeid(Derived)) {
        // code never executed
    }

    // using RTTI
    int arr[10];
    Derived d;
    Base *p = &d;
    cout << typeid(42).name() << ", "
         << typeid(arr).name() << ", "
         << typeid(std::string).name() << ", "
         << typeid(p).name() << ", "
         << typeid(*p).name() << endl;
}