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
    Bulk_quote bulk2;
    Bulk_quote *bulkP = &bulk2; // static and dynamic type are the same
    Quote *itemP = &bulk2;  // static and dynamic type are differ
    bulkP->discount_policy();   // ok : bulkP has type Bulk_Quote*
    itemP->discount_policy();   // error: itemP has type Quote*
    // even though bulk2 has a member named discount_policy, that member is not visible through itemP,
    // The type of itemP is a pointer to Quote, which means that the search for discount_policy starts in class Quote.

    // 3
    // were we write
    Derived3 d(42);
    cout << d.get_mem() < , endl;    // prints 42
}
