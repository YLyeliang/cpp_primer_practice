//
// Created by yel on 2021/3/7.
//
#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"
#include "165.h"
#include "set"
#include "unordered_set"

using namespace std;
// Template Specializations

int main() {
    // example 1
    const char *p1 = "hi", *p2 = "mom";
    compare(p1, p2); // the fisrt
    compare("hi", "mom");    // call the template with two nontype parameters

    // example 2
    // uses hash<Sales_data> and Sales_data operator== from 14.3
    unordered_multiset<Sales_data> SDSet;


}
