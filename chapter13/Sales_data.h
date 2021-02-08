//
// Created by fiberhome on 2020/11/13.
//

#ifndef NOW_CODE_SALES_DATA_H
#define NOW_CODE_SALES_DATA_H

#include "string"

using namespace std;

class Sales_data {
public:
    // copy control; use default
    Sales_data() = default;

    Sales_data(const Sales_data &);
//    Sales_data(const Sales_data &)=default;


    // synthesized copy-assignment operator
    Sales_data &operator=(const Sales_data &);

    ~Sales_data() = default;

private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};

Sales_data::Sales_data(const Sales_data &sd) :
        bookNo(sd.bookNo), // use the string copy constructor
        units_sold(sd.units_sold),
        revenue(sd.revenue) {}

//Sales_data &Sales_data::operator=(const Sales_data &) = default;

Sales_data &Sales_data::operator=(const Sales_data &rhs) {
    bookNo = rhs.bookNo;  // calls the string::operator=
    units_sold = rhs.units_sold; // use the built-in int assignment
    revenue = rhs.revenue;    //  uses the built-int double assignment
    return *this;   // return a reference to this object
}

// defining a Function as deleted
struct Nocopy {
    Nocopy() = default;   // use the synthesized default constructor
    Nocopy(const Nocopy &) = delete;       // no copy
    Nocopy &operator=(const Nocopy &) = delete; // no assignment
    // the destructor should not be a deleted member
    // since it will lead to the objects of this type could not be destroyed.
    ~Nocopy() = default; // use the synthesized destructor

    // other members
};
// The = delete signals to the compiler that we are intentionally not defining these members

class PrivateCopy {
    // no access specifier; following members are private by default;
    // copy control is private and so is inaccessible to ordinary user code
    PrivateCopy(const PrivateCopy &);

    PrivateCopy &operator=(const PrivateCopy &);
    // other members
public:
    PrivateCopy() = default;  // use the synthesized default constructor
    ~PrivateCopy() = default; // users can define objects of this type but not copy them
};
// friends and members of the class can still make copies.

#endif //NOW_CODE_SALES_DATA_H
