//
// Created by yel on 2021/2/25.
//
#include <vector>
#include "string"
#include "iostream"
#include "152.h"
#include "memory"
#include "set"


using namespace std;

// Containers and Inheritance

// when we use a container to store objects from an inheritance hierarchy, we generally must store those objects indirectly.
// Assume we define a vector to hold Bulk_Quote objects. We can't convert Quote objects to Bulk_Quote
// If we define a vector holds Quote, we can put Bulk_Quote into the container. However, these objects no longer be Bulk_Quote.
// example 1

// Put (Smart) Pointers, Not Objects, in Containers
// when we need a container that holds objects related by inheritance, we typically define the container to hold
// pointers( preferably smart pointers) to the base class.
// example 2

// 158.1 Writing a Basket class
// one of the ironies of oop in c++ is that we cannot use objects directly to support it. we must use inference and pointers
class Basket {
public:
    // Basket uses synthesized default constructor and copy-control members
    void add_item(const shared_ptr<Quote> &sale) {
        items.insert(sale);
    }

    double total_receipt(ostream &os) const;

private:
    // function to compare shared_ptrs needed to multiset members
    static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }

    // multiset to hold multiple quotes, ordered by the compare member
    multiset<shared_ptr<Quote>, decltype(compare) *> items{compare};
    // defining a multiset of shared_ptr to Quote object. will use a function with the same type as our compare member
    // to order the elements. Initializing items to use our compare function

};

// Defining the members of Basket
double print_total(ostream &os, const Quote &item, size_t n) {
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_Quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()   // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

// The second member, total_receipt, prints an itemized bill for the contents of the basket and returns the price for
// all the items in the basket.
double Basket::total_receipt(ostream &os) const {
    double sum = 0.0; // holds the running total
    // iter refers to the first element in a batch of elements with the same ISBN
    // upp_bound returns an iterator to the element just past the end of that patch
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        // we know there is at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << endl; // print the final overall total
    return sum;
}

// Hiding the Pointers
// Users of Basket still have to deal with dynamic memory, because add_item takes a shared_ptr.
// As a result, users have to write code such as in example 3:
// next, we redefine add_item so that it takes a Quote object instead of shared_ptr.
// define two versions, one that will copy its given object and the other that will move from it
void add_item(const Quote &sale);   // copy the given object
void add_item(Quote &&sale);    // move the given object
// The only problem is that add_item doesn't know what type to allocate. if with     new Quote(sale)
// since sale may be Quote or Bulk_Quote, this will only copies the Quote part of sale.

// Simulating virtual copy
// we'll solve above problem by giving our Quote class a virtual member that allocates a copy of itself
class Quote3 {
public:
    // virtual function to return a dynamically allocated copy of itself
    // these members use reference qualifiers:
    virtual Quote3 *clone() const &{ return new Quote3(*this); }

    virtual Quote3 *clone() &&{ return new Quote3(std::move(*this)); }
    // other members as before

    string isbn() const { return bookNo; }

    virtual double net_price(size_t n) const { return price * n; }

    virtual ~Quote3() = default; // dynamic binding for the destructor
private:
    std::string bookNo; // ISBN number
protected:
    double price = 0.0;   // normal, undiscounted price
};

class Bulk_quote3 : public Quote3 {
    Bulk_quote3 *clone() const &{ return new Bulk_quote3(*this); }

    Bulk_quote3 *clone() &&{ return new Bulk_quote3(std::move(*this)); }
    // other
};

// Using clone, it is easy to write our new versions of add_item:
class Basket2 {
public:
    void add_item(const Quote3 &sale)   // copy the given object
    { items.insert(shared_ptr<Quote3>(sale.clone())); }

    void add_item(Quote3 &&sale)  // move the given object
    { items.insert(shared_ptr<Quote3>(std::move(sale).clone())); }

    double total_receipt(ostream &os) const;

private:
    static bool compare(const shared_ptr<Quote3> &lhs, const shared_ptr<Quote3> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }

    multiset<shared_ptr<Quote3>, decltype(compare) *> items{compare};
};

int main() {
    // example 1
    vector<Quote> basket;
    basket.push_back(Quote("0", 50));
    // ok: but copies only the Quote part of the object into basket
    basket.push_back(Bulk_quote("1", 50, 10, 0.25));
    // calls versions defined by Quote, prints 750, i.e. 15 *50
    cout << basket.back().net_price(15) << endl;
    // The elements in baskets is Quote. When we add a Bulk_Quote to the vector its derived part is ignored.

    // example 2
    vector<shared_ptr<Quote>> basket2;
    basket2.push_back(make_shared<Quote>("0", 50));
    basket2.push_back(make_shared<Bulk_quote>("1", 50, 10, .25));
    // calls version defined by Bulk_Quote, prints 562.5. i.e 15 *50 less the discount
    cout << basket2.back()->net_price(15) << endl;

    // example 3
    Basket bsk;
    bsk.add_item(make_shared<Quote>("1", 45));
    bsk.add_item(make_shared<Bulk_quote>("2", 30, 10, .24));


}