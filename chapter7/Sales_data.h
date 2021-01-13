#include <utility>

//
// Created by fiberhome on 2020/12/8.
//

#ifndef NOW_CODE_SALES_DATA_H
#define NOW_CODE_SALES_DATA_H


// common way
//struct Sales_data {
//    // constructor added
//    Sales_data() = default; // only because we want to provide other constructors as well as the default constructor.
//
//    Sales_data(std::string s) : bookNo(std::move(s)) {}
//
//    Sales_data(std::string s, unsigned n, double p) :
//            bookNo(std::move(s)), units_sold(n), revenue(p * n) {}
//
//    Sales_data(std::istream &s);
//
//    // new members: operations on Sales_data objects
//    std::string isbn() const { return bookNo; }
//
//    Sales_data &combine(const Sales_data &);
//
//    double avg_price() const;
//
//    // data members
//    std::string bookNo;
//    unsigned units_sold = 0;
//    double revenue = 0.0;
//};

// with private and public
struct Sales_data {


    // a friend function can be defined inside the
    //class body. Such functions are implicitly

    //friend declarations for non-member operations added.
    friend Sales_data add(const Sales_data &, const Sales_data &);

    friend std::istream &read(std::istream &, Sales_data &);

    friend std::ostream &print(std::ostream &, const Sales_data &);

public:
    Sales_data() = default;

    Sales_data(const std::string &s, unsigned n, double p) :
            bookNo(s), units_sold(n), revenue(p * n) {};

    // can use explicit to prevent the use of a constructor in a context that requires
    // an implicit conversion.
    explicit Sales_data(const std::string &s) : bookNo(s) {};

    explicit Sales_data(std::istream &);

    std::string &isbn() const { return bookNo; }

    Sales_data &combine(const Sales_data &);

private:
//    double avg_price() const { return units_sold ? revenue / units_sold : 0; }
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// class and struct, only difference is the default access level.
// for struct: the member defined before the first access specifier( public and private) are public.
// for class: *** are private.

// Friends members declarations.
Sales_data add(const Sales_data &, const Sales_data &);

std::istream &read(std::istream &, Sales_data &);

std::ostream &print(std::ostream &, const Sales_data &);


//nonmember Sales_data interface functions.
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

// when members are private, the function can't access it. In this case,
// we need friend to allow another cls or func to access its non-public members.
std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

// constructor outside the class
Sales_data::Sales_data(std::istream &is) {
    read(is, *this);
}


// defining member function outside the class
// definition must match the declaration, param list, return type...
double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this; //return the object on which the function was called.
}


#endif //NOW_CODE_SALES_DATA_H
