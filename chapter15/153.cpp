//
// Created by yel on 2021/2/22.
//
#include "iostream"
#include "string"
#include "152.h"

using namespace std;

// Virtual Functions

// Calls to Virtual Functions may be resolved at run time

// the key idea behind oop is polymorphism(多态), which is derived from a Greek word meaning "many forms".


int main() {
    // rethink the print_total in 151.cpp, dynamic binding happens only when a virtual function
    // is called through a pointer or a reference
    Quote base("0", 50);
    Bulk_quote derived("1", 50, 5, .19);
    base = derived; // copies the Quote part of derived into base
    base.net_price(20); // calls Quote::net_price


}
