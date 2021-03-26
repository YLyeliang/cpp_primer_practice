//
// Created by fiberhome on 2021/3/25.
//

#ifndef NOW_CODE_198_H
#define NOW_CODE_198_H

#include "string"
#include "iostream"
#include "memory"
#include "set"
#include "vector"

using namespace std;

// Inherently Non-portable Features

// 198.1 Bit-fields
// A bit-field holds a specified number of bits
// A bit-field must have integral or enumeration type.
typedef unsigned int Bit;

class File {
    Bit mode: 2;    // mode has 2 bits
    Bit modified: 1; // modified has 1 bit
    Bit prot_owner: 3; // prot_owner has 3 bits
    Bit prot_group: 3; // prot_group has 3 bits
    Bit prot_world: 3; // prot_world has 3 bits
    // operations and data members of File
public:
    // file modes specified as octal literals; see § 2.1.3 (p. 38)
    enum modes {
        READ = 01, WRITE = 02, EXECUTE = 03
    };

    File &open(modes);

    void close();

    void write();

    bool isRead() const;

    void setWrite();

};

// Using Bit-fields
void File::write() {
    modified = 1;
}

void File::close() {
    if (modified);
}

File &File::open(modes m) {
    mode |= READ;    // set the READ bit by default
    if (m & WRITE)  // if opening READ and WRITE
        // processing to open the file in read/write mode
        ;
    return *this;
}

inline bool File::isRead() const { return mode & READ; }

inline void File::setWrite() { mode |= WRITE; }

// 198.2 volatile qualifier
// a program might contain a variable updated by the system clock. An object should be
// declared volatile when its value might be changed in ways outside the control or detection of the program
volatile int display_register;  // int value that might change
volatile int iax[100];  // each element in iax is volatile
// see example 1

// Synthesized copy does not apply to volatile objects
// If a class wants to allow volatile objects to be copied, moved, or assigned, it
// must define its own versions of the copy or move operation.
class Foo {
public:
    Foo(const volatile Foo &); // copy from a volatile object
// assign from a volatile object to a nonvolatile object
    Foo &operator=(volatile const Foo &);

// assign from a volatile object to a volatile object
    Foo &operator=(volatile const Foo &) volatile;
// remainder of class Foo
};

// 198.3 Linkage Directives: extern "C"
// Not implemented.

#endif //NOW_CODE_198_H
