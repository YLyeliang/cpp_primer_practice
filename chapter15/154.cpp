//
// Created by yel on 2021/2/23.
//

#include "string"
#include "iostream"
#include "152.h"

using namespace std;

// Abstract base class

// Pure Virtual Functions
// a pure virtual function does not have to be defined. by writing = 0 in place of a function body
// class to hold the discount rate and quantity
// derived classes will implement pricing strategies using these data
class Disc_quote : public Quote {
public:
    Disc_quote() = default;

    Disc_quote(const string &book, double price, size_t qty, double disc) :
            Quote(book, price), quantity(qty), discount(disc) {}

    double net_price(size_t) const = 0; // pure virtual

private:
    size_t quantity = 0;
    double discount = 0.0;
};

// Classes with pure virtual are abstract base classes
// we cannot create(directly) objects of a type that is an abstract base class.
Disc_quote discounted;  // error: can't define a Disc_quote object
Bulk_quote bulk;    // ok: has no pure virtual functions
// classes that inherit from Disc_quote must define net_price or those classes will be abstract as well

// A derived class constructor initializes its direct base class only
// the discount kicks in when a specified number of copies of the same book are sold
// the discount is expressed as a fraction to use to reduce the normal price
class Bulk_quote3 : public Disc_quote {
public:
    Bulk_quote3() = default;

    Bulk_quote3(const string &book, double price, size_t qty, double disc) :
            Disc_quote(book, price, qty, disc) {}

    // overrides the base version to implement the bulk purchase discount policy
    double net_price(size_t) const override;
};


