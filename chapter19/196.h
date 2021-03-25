//
// Created by fiberhome on 2021/3/25.
//

#ifndef NOW_CODE_196_H
#define NOW_CODE_196_H

#include "string"
#include "iostream"
#include "memory"
#include "set"
#include "vector"

using namespace std;

// union: A space-saving class
// union is a special kind of class
// A union may have multiple data member, but at any point in time, only one of the members may have a value
// when a value is assigned to one member, other members become undefined
// A union can't have a member that is a reference

// Defining an union
// objects of type Token have a single member, which could be of any of the listed types
union Token {
    // members are public by default
    char cval;
    int ival;
    double dval;
};

// Using union type
Token first_token = {'a'};  // initializes the cval member
Token second_token = {1};   // ... ival
Token last_token;
Token *pt = new Token;  // pointer to uninitialized ..
// access see example 1

// Anonymous unions
static union {
    char cval;
    int ival;
    double dval;
};  // defines an unnamed object, whose members we can access directly
// see example 2

// unions with members of class type

// using a class to manage union members
class Token2 {
public:
    // copy control needed because our class has a union with a string member
    // defining the move constructor and move-assignment operator is left as an exercise
    Token2() : tok(INT), ival(0) {}

    Token2(const Token2 &t) : tok(t.tok) { copyUnion(t); }

    Token2 &operator=(const Token2 &);

    // if the union holds a string, we must destroy it;
    ~Token2() { if (tok == STR)sval.~string(); }

    // assignment operators to set the differing members of the union
    Token2 &operator=(const std::string &);

    Token2 &operator=(char);

    Token2 &operator=(int);

    Token2 &operator=(double);


private:
    enum {
        INT, CHAR, DBL, STR
    } tok;
    union {
        char cval;
        int ival;
        double dval;
        std::string sval;
    };  // each Token object has an unnamed member of this unnamed union type
    // check the discriminant and copy the union member as appropriate
    void copyUnion(const Token2 &);
};

// Managing the Discriminant and Destroying the string
Token2 &Token2::operator=(int i) {
    if (tok == STR) sval.~string(); // if we have a string, free it
    ival = i;   // assign to the appropriate member
    tok = INT;  // update the discriminant
    return *this;
}

Token2 &Token2::operator=(const string &s) {
    if (tok == STR)  // if we already hold a string, just do an assignment
        sval = s;
    else
        new(&sval) string(s);   // otherwise construct a string
    tok = STR;
    return *this;
}

// Managing union members that require copy control
void Token2::copyUnion(const Token2 &t) {
    switch (t.tok) {
        case Token2::INT:
            ival = t.ival;
            break;
        case Token2::CHAR:
            cval = t.cval;
            break;
        case Token2::DBL:
            dval = t.dval;
            break;
        case Token2::STR:
            new(&sval) string(t.sval);
            break;
    }
}

Token2 Token2::operator=(const Token2 &t) {
    // if this object object holds a string and t doesn't, we have to free old string
    if (tok == STR && t.tok != STR) sval.~string();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else
        copyUnion(t);   // will construct a string if t.tok is STR
    tok = t.tok;
    return *this;

}

#endif //NOW_CODE_196_H
