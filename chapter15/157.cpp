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
    Quote() = default;

    Quote(const Quote &) = default;  // memberwise copy
    Quote(Quote &&) = default;   // memberwise copy
    Quote &operator=(const Quote &) = default;   // copy assign
    Quote &operator=(Quote &&) = default;  // move assign

    // virtual destructor is needed if a base pointer pointing to a derived object is deleted
    virtual ~Quote() = default;   // dynamic binding for the destructor
};

class Disc_Quote : public Quote {
    Disc_Quote() = default;
};

class Bulk_Quote : public Quote {
};

// Synthesized Copy control and Inheritance

// Base classes and deleted copy control in the derived
class B {
public:
    B();

    B(const B &) = delete;
    // other
};

class D : public B {
    // no constructors
};
// example see 2

// Move Operations and Inheritance
// classes derived from a base class that doesn't have move operations don't get synthesized move operations
// see Quote

// Derived-Class Copy-control Members

// Defining a Derived copy or move constructor
// when we define a copy or move constructor for a derived class, we ordinarily use the corresponding base-class
// constructor to initialize the base part of the object:
class Base2 {
};

class D2 : public Base2 {
public:
    // by default, the base class default constructor initializes the base part of an object
    // to use the copy or move constructor, we must explicitly call that
    // constructor in the constructor initializer list
    D2(const D2 &d) : Base2(d) // copy the base members
    {}

    // probably incorrect definition of the D2 copy constructor
    // base-class part is default initialized, not copied
    D2(const D2 &d)  // member initializers, but no base-class initializer
    {}

    D2 &operator=(const D2 &);

    D2(D2 &&d) : Base2(std::move(d)) // move the base members
    {}

    // Base2::~Base2 invoked automatically
    ~D2() {}
};
// Had the initializer for the base class has been omitted, see above copy control

// Derived-class assignment operator
// like the copy and move, a derived-class assignment operator must assign its base part explicitly
// Base2::operator=(const Base2&) is not invoked automatically
D2 &D2::operator=(const D2 &rhs) {
    Base2::operator=(rhs);  // assign the base part
    // assign the members in the derived class, as usual,
    // handling self-assignment and freeing existing resources as appropriate
    return *this;
}

// Derived-class destructor
// a derived destructor is responsible only for destroying the resources allocated by the derived class
// see above destructor
// objects are destroyed in the opposite order from which they are constructed:
// The derived destructor is first, then the base-class destructors are invoked

// Calls to Virtual in constructors and destructors
// consider what would happen if the derived-class version of a virtual was called from the base-class constructor.
// since those members are uninitialized while a base constructor is running. If such access were allowed, may crash.

// Inherited Constructors
// a class cannot inherit the default, copy, and move constructors.
// a derived class inherits its base-class constructors by providing a using declaration that names its base class.
// As a example, we can redefine the Bulk_Quote inherited from Disc_Quote
class Bulk_Quote2 : public Disc_Quote {
public:
    using Disc_Quote::Disc_Quote;   // inherits disc_quote's constructor
    double net_price(size_t) const;
};

int main() {
    // 1
    Quote *itemP = new Quote;   // same static and dynamic type
    delete itemP;   // destructor for Quote called
    itemP = new Bulk_Quote;   // static and dynamic differ
    delete itemP;   // destructor for Bulk_Quote called

    // 2
    D d;    // ok: D's synthesized default constructor uses B's default constructor
    D d2(d);    // error: D's synthesized copy constructor is deleted
    D d3(std::move(d)); // error: implicitly uses D's deleted copy constructor

}