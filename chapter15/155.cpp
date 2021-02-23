//
// Created by yel on 2021/2/23.
//
#include "string"
#include "iostream"

using namespace std;
// Access Control and Inheritance
// each class also controls whether its members are accessible to a derived class

// protected members
// protected can be thought of as a blend of private and public:
// like private, protected members are inaccessible to users of the class
// like public, protected members are accessible to members and friends of classes derived from this class
// In addition,
// A derived class member or friend may access the protected members of the base class only through a derived object.
// The derived class has no special access to the protected members of base-class object.
class Base {
    // added friend declaration; other members are as before
    friend class Pal;   // Pal has no access to classes derived from Base
protected:
    int prot_mem;
};

class Sneaky : public Base {
    friend void clobber(Sneaky &);   // can access Sneaky::prot_mem
    friend void clobber(Base &);    // can't access Base::prot_mem
    int j;  // j is private
};

// ok: clobber can access the private and protected members in Sneaky objects
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }

// error: clobber can't access the protected members in Base
void clobber2(Base &s) { s.prot_mem = 0; }

// public, private, and protected Inheritance
class Base2 {
public:
    void pub_mem();

private:
    char priv_mem;

protected:
    int prot_mem;
};

struct Pub_Derv : public Base2 {
    // ok: derived class can access protected members
    int f() { return prot_mem; }

    // error: private members are inaccessible to derived classes
    char g() { return priv_mem; }
};

struct Pri_Derv : private Base2 {
    // private derivation doesn't affect access in the derived class
    int f1() const { return prot_mem; }
};

// The derivation access specifier has no effect on whether members of a derived class may access the members
// of its own direct base class
// the purpose of the derivation access specifier is to control the access that users of the derived class
// example see 1 in main

struct Derived_from_public : public Pub_Derv {
    // ok: Base::prot_mem remains protected in Pub_Derv
    int use_base() { return prot_mem; }
};

struct Derived_from_private : public Pri_Derv {
    // error: ... is private in Pri_Derv
    int use_baes() { return prot_mem; }
};

// Accessibility of Derived-to-Base Conversion
// Assuming D inherits from B:
// User code may use the derived-to-base conversion only if D publicly inherited from B.
// Member functions and friends of D can use the conversion to B regardless how D inherits from B
// Member functions and friends of classes derived from D may use the ... if D inherits from B using either public or
// protected.

// Friendship and Inheritance
// friends of the base type have no special access to members of its derived classes
// friends of a derived class have no special access to the base class
// see Base at the start
class Pal {
public:
    int f(Base b) { return b.prot_mem; }    // ok: Pal is a friend of Base
    int f2(Sneaky s) { return s.j };  // error: not friend
    // access to a base class is controlled by the base class, even inside a derived object
    int f3(Sneaky s) { return s.prot_mem; }   // ok: Pal is friend
};

// D2 has no access to protected or private members in Base
class D2 : public Pal {
    int mem(Base b) { return b.prot_mem; }  // error: friendship doesn't inherit
};

// Exempting Individual Members
// Sometimes we need to change the access level of a name that a derived class inherits.
class Base3 {
public:
    size_t size() const { return n; }

protected:
    size_t n;
};

class Derived : private Base3 {
public:
    // maintain access levels for members related to the size of the object
    using Base3::size;
protected:
    using Base3::n;
};
// Derived uses private inheritance, size and n are private members of Derived. The using adjust the accessibility
// of these members. Users of Derived can access the size, and classes subsequently derived from Derived can access n.

// Default Inheritance Protection Levels
// same as class and struct
struct D1 : Base {
};  // public inheritance default;
class D3 : Base {
};    // private ...;

int main() {
    // 1
    Pub_Derv d1;    // members inherited from Base are public
    Pri_Derv d2;    // members inherited from Base are private
    d1.pub_mem();   // ok: public
    d2.pub_mem();   // error: private

}
