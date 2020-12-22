//
// Created by fiberhome on 2020/12/8.
//
// Sales_data
#include "iostream"
#include "Sales_data.h"

using namespace std;


int main() {
    Sales_data total;
    if (read(cin, total)) {
        Sales_data trans;
        while (read(cin, trans)) {
            // implicitly call `this`. equivalent to Sales_data::isbn(&total)
            // `this` is a const pointer.
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    } else {
        cerr << "No data?!" << endl;
    }
}