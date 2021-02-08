//
// Created by yel on 2021/2/3.
//

#include "string"
#include "vector"
#include "memory"
#include "./Sales_data.h"

using namespace std;

int main() {
    string dot(10, '.'); // direct initialization
    string s(dot); // direct
    const string &s2 = dot; // copy
    string null_block = "00000"; //copy
    string nines = string(100, '9'); //copy

    // constraints on copy initialization
    vector<int> v1(10);  // ok direct
    vector<int> v2 = 10;   // error, constructor that takes a size is explicit
    void f(vector<int>); // f's parameter is copied initialized
    f(10); // error: can't use an explicit constructor to copy an argument
    f(vector<int>(10)); // ok directly construct a temporary vector from int

    // The copy-assignment operator
    Sales_data trans, accum;
    trans = accum; //uses the Sales_data copy-assignment operator

    // whether a class needs to define its own versions of copy-control members is to decide first
    // whether the class needs a destructor

    // if a class needs a destructor, it almost surely also needs the copy-assignment operator and a copy constructor.

    // using = default see .h file


}

void destructor_test() {   // new scope
    // p and p2 point to a dynamically allocated objects
    Sales_data *p = new Sales_data; // p is built-in pointer
    auto p2 = make_shared<Sales_data>();    // p2 is shared_ptr
    Sales_data item(*p);    // copy constructor copies *p into item
    vector<Sales_data> vec; // local object
    vec.push_back(*p2);     // copies the object to which p2 points.
    delete p; // destructor called on the object pointed by p

} // exit local scope, destructor called on item, p2, and vec
// destroying p2 decrement the use count; if counts goes to 0, the object is freed
// destroying vec destroys the elements in vec


