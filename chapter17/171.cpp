//
// Created by fiberhome on 2021/3/8.
//

#include "string"
#include "tuple"
#include "vector"
#include "list"
#include "../chapter13/Sales_data.h"

using namespace std;
// The tuple type
// tuple is a template that similar to a pair. each pair type has different types for its members, but ever pair
// always has exactly two members.
// tuple can have any number of members.

int main() {
    // 171.1 Defining and initializing tuples
    tuple<size_t, size_t, size_t> threeD;   // all three members set to 0
    tuple<string, vector<double>, int, list<int>> someVal("constants", {3.14, 2}, 1, {0, 1, 2, 3, 4});
//    tuple<size_t, size_t, size_t> threeD = {1, 2, 3};    // error
    tuple<size_t, size_t, size_t> threeD2{1, 2, 3}; // ok
    // same as make_pair
    // isbn, count, price
    auto item = make_tuple("abc", 1, 20.0);

    // Accessing the members of tuple
    // A pair always has two members, first and second. we access the members of tuple through get
    auto book = get<0>(item);    // returns the first member of item
    auto cnt = get<1>(item);
    auto price = get<2>(item) / cnt;
    get<2>(item) *= 0.8;
    // if we have a tuple whose precise type details we don't know, we can use two auxiliary class templates to find
    typedef decltype(item) trans;   // trans is the type of item
    // returns the number of members in object's of type trans
    size_t sz = tuple_size<trans>::value;   // returns 3
    // cnt has the same type as the second member in item
    tuple_element<1, trans>::type cnt2 = get<1>(item);    // cnt is an int

    // Relational and equality operators
    // relational and equality operators behave similar to containers
    tuple<string, string> duo("1", "2");
    tuple<size_t, size_t> twoD(1, 2);
    bool b = (duo == twoD); // error: can't compare size_t and a string
    b = (twoD < threeD2);  // error: differing number of members
    tuple<size_t, size_t> origin(0, 0);
    b = (origin < twoD);   // ok: b is true

    // 171.2 Using a tuple to return multiple values
    // a common use of tuple is to return multiple values from a function
    // assume we have a file of transactions for each store
    // each element in files holds the transactions for a particular store
    vector<vector<Sales_data>> files;
    // write a function to search files looking for the stores that sold a given book
    // for each store that matching, creat a tuple to hold the index and two iterators
    // function see 171.h


    return 0;


}