//
// Created by fiberhome on 2021/3/24.
//

#ifndef NOW_CODE_194_H
#define NOW_CODE_194_H

#include "string"
#include "iostream"

using namespace std;

// Pointer to Class Member
// a pointer that can point to a non-static member of a class
class Screen {
public:
    typedef std::string::size_type pos;

    // data is a static member that returns a pointer to member
    static const std::string Screen::*data() { return &Screen::contents; }

    char get_cursor() const { return contents[cursor]; }

    char get() const;

    char get(pos ht, pos wd) const;

private:
    std::string contents;
    pos cursor;
    pos height, width;
};

// 194.1 Pointers to Data members
// pdata can point to a string member of a const (or non-const) screen object
// see example 1

// A function returning a pointer to data member
// above pdata would be an error since contents is private. Instead, it would define a function to return a pointer to
// that member. see Screen static const
// example 2

// 194.2 Pointers to member functions
// The easiest way to form a pointer to member function is to use auto
// example 3



#endif //NOW_CODE_194_H
