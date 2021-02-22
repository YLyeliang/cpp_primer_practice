//
// Created by yel on 2021/2/22.
//

#include "string"
#include "iostream"

using namespace std;

// OOP: An Overview
// Suppose we have a bookstore, there are kinds of discount to different books, and buying numbers.

// Inheritance
// base class, derived classes
// Quote represent un-discounted books
// From Quote, inherit a second class, Bulk_quote, to represent books that can be sold with a quantity discount

// In c++, the base class defines as virtual those functions it expects its derived classes to define for themselves.
class Quote {
public:
    std::string isbn() const;

    virtual double net_price(std::size_t n) const;
};

class Bulk_Quote : public Quote { // Bulk_quote inherits from Quote
public:
    double net_price(std::size_t) const override;
};
// Because Bulk_quotes uses public in its derivation list. We can use objects of type Bulk_Quote as if they were Quote.
// A derived class must include its own class body a declaration of all the virtual functions it intends to define
// for itself. New standard add override keyword to override a virtual that it inherits.

// Dynamic Binding

// calculate and print the price for the given number of copies, applying any discounts
double print_total(ostream &os, const Quote &item, size_t n) {
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_Quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()   // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main() {
    // basic has type Quote;bulk has type Bulk_quote
    print_total(cout, basic, 20); // calls Quote version of net_price
    print_total(cout, bulk, 20);  // calls Bulk_Quote version of net_price
}