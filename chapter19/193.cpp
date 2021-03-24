//
// Created by fiberhome on 2021/3/23.
//

#include "string"
#include "iostream"

using namespace std;

// Enumerations
// c++ has two kinds of enumerations: scoped and unscoped.
// new standard introduced scoped enumerations
// enum class
enum class open_modes {
    input, output, append
};
// here we defined an enumeration type that has three enumerators.

// unscoped enumeration
enum color {
    red, yellow, green
};
// unnamed,unscoped enum
enum {
    floatPrec = 6, doublePrec = 10, double_doublePrec = 10
};

// Enumerators
// obey normal scoping rules
enum stopligh {
    red, yellow, green
};    // error: redefines enumerators
enum class peppers {
    red, yellow, green
};  // ok: enumerators are hidden
color eyes = green; // ok: enumerators are in scope for an unscoped enumeration
peppers p = green;  // error: enumerators from peppers are not in scope, color::green is in scope but has the wrong type
color hair = color::red;    // ok: we can explicitly access the enumerators
peppers p2 = peppers::red;  // ok: using red from peppers

// By default, enumerator values start at 0 and each enumerator has a value 1 greater than the preceding one.
// initializers can still be supplied.
enum class intTypes {
    charTyp = 8, shortTyp = 16, intTyp = 16, longTyp = 32, long_longType = 64
};
// enumerators are const, if initialized, their initializers must be constant expressions.
constexpr intTypes charbits = intTypes::charTyp;
// we can use enum as the expression in a switch statement

// Like Classes, Enumerations define new types

// Specifying the size of an enum
enum intValues : unsigned long long {
    charTyp = 255, shortTyp = 65535, intTyp = 65535,
    longTyp = 4294967295UL,
    long_longTyp = 18446744073709551615ULL
};

// Forward Declarations for enumerations
// forward declaration of unscoped enum named intValues
enum intValues : unsigned long long;    // unscoped, must specify a type
enum class open_modes;  // scoped enums can use int by default
// error: declarations and definition must agree whether the enum is scoped or unscoped
enum class intValues;
enum intValues; // error: intValues previously declared as scoped enum
enum intValues : long;  // error: intValues previously declared as int

// parameter matching and enumerations
// unscoped enumeration; the underlying type is matching dependent
enum Tokens {
    INLINE = 128, VIRTUAL = 129
};

void ff(Tokens);

void ff(int);

void newf(unsigned char);

void newf(int);

unsigned char uc = VIRTUAL;


int main() {
    // Like Classes, Enumerations define new types
    open_modes om = 2;  // error: 2 is not of type open_modes
    om = open_modes::input; // ok: input is an enumerator of open_modes
    int i = color::red; // ok: unscoped enumerator implicitly converted to int
    int j = peppers::red;   // error: scoped enumerations are not implicitly converted


    Tokens curTok = INLINE;
    ff(128);    // exactly matches ff(int)
    ff(INLINE); // exactly matches ff(Tokens)
    ff(curTok); // exactly matches ff(Tokens)

    newf(VIRTUAL);  // calls newf(int)
    newf(uc);   // calls newf(unsigned char)

    return 0;
}

