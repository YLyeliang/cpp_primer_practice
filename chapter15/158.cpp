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
// The second member, total_receipt, prints an itemized bill for the contents of the basket and returns the price for
// all the items in the basket.
double Basket::total_receipt(ostream &os) const{
    double sum=0.0; // holds the running total
    // iter refers to the first element in a batch of elements with the same ISBN

}

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


}