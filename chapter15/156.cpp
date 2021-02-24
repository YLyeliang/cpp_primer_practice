//
// Created by fiberhome on 2021/2/23.
//

#include "string"
#include "iostream"
#include "152.h"

using namespace std;

// Class Scope Under Inheritance

// If a name is unresolved within the scope of the derived class, the enclosing base-class scopes are searched
// for a definition of that name.
// see 1 in main

// Name lookup happens at compile time

class Disc_quote : public Quote {
public:
    pair<size_t, double> discount_policy() const { return {quantity, discount}; }
    // other members as before
private:
    size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote3 : public Disc_quote {
public:
    Bulk_quote3() = default;

    Bulk_quote3(const string &book, double price, size_t qty, double disc) :
            Disc_quote() {}

    // overrides the base version to implement the bulk purchase discount policy
    double net_price(size_t) const override;


};

// we can use discount_policy only through an object, pointer, or reference of type Disc_quote or of a class derived from Disc_quote:
// see 2 in main

// Name Collisions and Inheritance
// A derived-class member with the same name as a member of the base class hides direct use of the base-class member
struct Base3 {
    Base3() : mem(0) {}

protected:
    int mem;
};

struct Derived3 : Base3 {
    Derived3(int i) : mem(i) {}  // initializes Derived3::mem to i. Base::mem is default initialized
    int get_mem() { return mem; }   // return Derived3::mem

protected:
    int mem;    // hides mem in the base
};
// the use to see 3 in main

// using the scope operator to use hidden members
struct Derived4 : Base3 {
    int get_mem() { return Base3::mem; }
};
// If we ran the code in 3, the result of d.get_mem() would be 0.

// As usual, name lookup happens before type checking
// function declared in an inner scope do not overload functions declared in an outer scope.
// As a result, functions defined in a derived class do not overload members defined in its base class.
// The derived member hides the base-class member within the scope of the derived class if has the same name.
struct Base4 {
    int memfcn();
};

struct Derived5 : Base4 {
    int memfcn(int);    // hides memfcn in the base
};
// Instance see 4

// Virtual functions and scope
// If the base and derived members took arguments that differed from one another, there would be no way to call the
// derived version through a reference or pointer to the base class
class Base5 {
public:
    virtual int fcn();
};

class D1 : public Base5 {
public:
    // hides fcn in the base; this fcn is not virtual
    // D1 inherits the definition of Base5::fcn()
    int fcn(int);   // parameter list differs from fcn in Base5
    virtual void f2();  // new virtual function that does not exist in Base5
};

class D2 : public D1 {
public:
    int fcn(int);   // non-virtual function hides D1::fcn(int)
    int fcn();  // overrides virtual fcn from Base5
    void f2();  // overrides virtual f2 from D1
};

// Calling a Hidden Virtual through the Base class
// given the classes above, let's look at several different ways to call these functions
// see 5

//Overriding Overloaded functions
// A derived class can override zero or more instances of the overloaded functions it inherits
// sometimes a class needs to override some of the functions in an overloaded set. It would be tedious to override
// every base-class version
// Thus, a derived class can provide a using declaration for the overloaded member
int main() {
    // 1
    Bulk_quote bulk;
    cout << bulk.isbn();
    // the use of the name isbn is resolved as follow:
    // 1. we called isbn on an object of type Bulk_quote, the search starts in Bulk_quote class. The name isbn is not found in that class
    // 2. Bulk_quote is derived from Disc_Quote, the Disc_quote is searched next. The name is still not found.
    // 3. Disc_quote is derived from Quote, the Quote class is searched next. The name isbn is found in that class;
    // the use of isbn is resolved to the isbn in Quote.

    // 2
    Bulk_quote3 bulk2;
    Bulk_quote3 *bulkP = &bulk2; // static and dynamic type are the same
    Quote *itemP = &bulk2;  // static and dynamic type are differ
    bulkP->discount_policy();   // ok : bulkP has type Bulk_Quote*
    itemP->discount_policy();   // error: itemP has type Quote*
    // even though bulk2 has a member named discount_policy, that member is not visible through itemP,
    // The type of itemP is a pointer to Quote, which means that the search for discount_policy starts in class Quote.

    // 3
    // were we write
    Derived3 d(42);
    cout << d.get_mem() < , endl;    // prints 42

    // 4
    Derived5 d5;
    Base4 b4;
    b4.memfcn();    // calls Base4::memfcn
    d5.memfcn(10);  // calls Derived5::memfcn
    d5.memfcn();    // error: memfcn with no arguments is hidden
    d5.Base4::memfcn(); // ok: calls Base4::memfcn

    // 5
    Base5 bobj;
    D1 d1obj;
    D2 d2obj;
    Base5 *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    bp1->fcn(); // virtual call: Base5::fcn
    bp2->fcn(); // virtual call: Base5::fcn
    bp3->fcn(); // virtual call: D2::fcn
    D1 *d1p = &d1obj;
    D2 *d2p = &d2obj;
    bp2->f2();  // error: Base5 has no member named f2
    d1p->f2();  // virtual call: D1::f2
    d2p->f2();  // virtual call: D2::f2
    // The first three call, Because fcn is virtual, the compiler generates code to decide at run time which version to call.
    // let's look at non-virtual call
    Base5 *p1 = &d2obj;
    D1 *p2 = &d2obj;
    D2 *p3 = &d2obj;
    p1->fcn(42);    // error: has no version of fcn that takes an int
    p2->fcn(42);    // statically bound, calls D1::fcn(int)
    p3->fcn(42);    // statically bound, calls D2::fcn(int)


}
