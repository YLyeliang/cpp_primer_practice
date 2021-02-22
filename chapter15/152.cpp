//
// Created by yel on 2021/2/22.
//
#include "string"
#include "iostream"
#include "152.h"

using namespace std;
// Defining Base and Derived classes

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

    // there is no implicit conversion from base to derived ...
    Quote base;
    Bulk_quote *bulkp = &base; // error: can't convert base to derived
    Bulk_quote &bulkRef = base; // error: can't convert base to derived
    // cannot convert from base to derived even when a base pointer or reference is bound to a derived object
    Bulk_quote bulk2;
    Quote *itemP = &bulk2;   // ok: dynamic type is Bulk_quote
    Bulk_quote *bulkP = itemP;  // error: can't convert base to derived

    // ... and no conversion between objects
    Bulk_quote bulk3;
    Quote item2(bulk3); // uses the Quote::Quote(const Quote&) constructor
    item2 = bulk2;  // calls Quote::operator = (const Quote&)
    // only Quote part of bulk are copied and assigned. We say that the Bulk_quote portion of bulk is sliced down.




}