//
// Created by yel on 2021/2/19.
//

#include "string"
#include "iostream"
#include "../Sales_data.h"
#include "vector"

using namespace std;

// Input and Output Operators

// overloading the output operator <<
ostream &operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

// overloading the input operator >>
istream &operator>>(istream &is, Sales_data &item) {
    double price;   // no need to initializes; we'll read into price before we use it
    is >> item.bookNo >> item.units_sold >> price;
    if (is) // check that the inputs succeeded
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();    // input failed; give the object the default state
    return is;
}

// assumes that both objects refers to the same book
Sales_data
operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;   // copy data members from lhs into sum
    sum += rhs; // add rhs into sum
    return sum;
}

// Equality operators
bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() == rhs.isbn() &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
    return !(lhs == rhs);
}
// The definition of equality are trivial.

// Relational operators
// Ordinarily the relational operators should
// 1. Define an ordering relation that is consistent with the requirements for use as a key to an associative container;
// 2. Define a relation that is consistent with == if the class has both operators.

// compound assignment operators
Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}


int main() {
    // overloading the output operator <<

    // IO operators must be nonmember functions
    Sales_data data;
    data << cout;   // if operator<< is a member of Sales_data
    // usually, IO operators must be declared as friends

    // overloading the input operator >>


    // 143 Arithmetic and Relational Operators
    // Ordinarily, we define the arithmetic and relational operators as nonmember functions

    // Equality operators

    // Relational operators

    // 144 Assignment Operators
    // In addition to the copy- and move-assignment that assign the same type.
    // a class can define additional assignment operators that allow other types as the right-hand operand

    // for example, the vector
    vector<string> v;
    v = {"a", "b"};
    // we can add this operator to our StrVec as well.
    // see 135.h

    // compound assignment operators
    // which are not required to be members. However, we prefer to define all assignments, including compound assignment,
    // in the class.

    // 145 Subscript Operator
    // The subscript operator must be a member function
    // If a class has a subscript operator, it usually should define two versions: one that returns a plain reference,
    // other that is a const member and returns a reference to const
    // As a example, see StrVec in 135.h

    // 146 Increment and Decrement Operators
    // these operators change the state of the object on which they operate, our preference is to make them members.
    // define increment or decrement operators should define both the prefix and postfix versions
    // see StrBlobPtr class in chapter12/StrBlobptr.h

}
