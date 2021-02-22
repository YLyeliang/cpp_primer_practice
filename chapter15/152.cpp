//
// Created by yel on 2021/2/22.
//
#include "string"
#include "iostream"

using namespace std;
// Defining Base and Derived classes

//152.1 Defining a base class
class Quote {
public:
    Quote() = default;    // =default see 71.4
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}

    string isbn() const { return bookNo; }

    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(size_t n) const { return price * n; }

    virtual ~Quote() = default; // dynamic binding for the destructor
private:
    std::string bookNo; // ISBN number
protected:
    double price = 0.0;   // normal, undiscounted price
};
// base class almost always define a virtual destructor
// base class specifies that a member function should be dynamically bound with keyword virtual
// and must be inside rather than outside the class body
// member functions that are not declared as virtual are resolved at compile time, not run time.

// Access Control and Inheritance
// sometimes a base class has members that it wants to let its derived classes use while still prohibiting
// access to those same members by other users. With keyword protected

// 152.2 Defining a Derived class
class Bulk_quote : public Quote { // inherits from Quote

    Bulk_quote(const string &, double, size_t, double);

    // overrides the base version in order to implement the bulk purchase discount policy
    double net_price(std::size_t) const override;

public:
    Bulk_quote() = default;

private:
    size_t min_qty = 0;  // minimum purchase for the discount to apply
    double discount = 0.0;    // fractional discount to apply
};
// virtual functions in the derived class

// derived-class objects and the derived-to-base conversion

// derived-class constructor
// see constructor in Bulk_quote
Bulk_quote::Bulk_quote(const string &book, double p, size_t qty, double disc) :
        Quote(book, p), min_qty(qty), discount(disc) {}
// the base class is initialized first

// using members of base class from the derived class
double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

// Inheritance and static members
// there is only one such member defined for the entire hierarchy
class Base {
public:
    static void statmem();
};

class Derived : public Base {
    void f(const Derived &);
};

void Derived::f(const Derived &derived_obj) {
    Base::statmem();    // ok: Base defines statmem
    Derived::statmem(); // ok: Derived inherits statmem
    // ok: derived objects can be used to access static from base
    derived_obj.statmem();  // access through a derived object
    statmem();  // access through this ojbect
}

// Declaration of derived classes
// The delcaration contains the class name but does not include its derivation list
class Bulk_quote : public Quote;    // error: derivation list can't appear here
class Bulk_quote;   // ok

// classes used as a base class
class Quote2;    // declared but not defined
// error: quote must be defined
class Bulk_quote2 : public Quote2 {
};

// Preventing Inheritance
// by following the class name with final
class NoDerived final {/* */};    // NoDerived can't be a base class
class Base2 {
};

// Last is final, we can't inherit from Last
class Last final : Base2 {
}; // Last can't be a base class
class Bad : NoDerived {
};    // error
class Bad2 : Last {
}; // error

// 152.3 Conversions and Inheritance
// understanding conversions between base and derived classes is essential to understanding how oop works in c++
// Ordinarily, we can bind a reference or pointer only to an object that has the same type as the corresponding
// reference or pointer or to a type that involves an acceptable const conversion
// While in classes related by inheritance, we can bind a reference or a pointer to a base-class type to an object of
// a type derived from that base class.
// For example, use Quote& to refer to Bulk_quote object

// static type and dynamic type
// The static type is known at compile time, dynamic type may not know until un time
// for example, see main()

// there is no implicit conversion from base to derived ...



int main() {
    // derived-class objects and the derived-to-base conversion
    Quote item;     // object of base type
    Bulk_quote bulk;    // object of derived type
    Quote *p = &item;   // p points to quote object
    p = &bulk;       // p points to the quote part of bulk
    Quote &r = bulk;    // r bound to the quote part of bulk

    // for example, static type and dynamic type. when print_total calls net_price
    double ret = item.net_price(n);
    // we know that item is Quote&. The dynamic type depends on the type of the argument to which item is bound
    // that type cannot be know until a call is executed at run time.

}