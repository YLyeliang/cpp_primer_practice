//
// Created by fiberhome on 2020/12/7.
//

#include "iostream"
#include "string"
#include "vector"
#include "cassert"

using namespace std;

// given a function. This function has type bool(const string &, const string &)
bool lengthCompare(const string &, const string &) { return true; }

string::size_type sumLength(const string &, const string &);

bool cstringCompare(const char *, const char *);


// pointers to overloaded functions
void ff(int *);

void ff(unsigned int);


int main() {
    // the pointer to this function, should like this:
    bool (*pf)(const string &, const string &);
    // When using the name of function as a value, the function is automatically converted to pointer
    pf = lengthCompare;
    pf = &lengthCompare;
    // two above are equivalent.

    // to call like this, below are equivalent.
    bool b1 = pf("hello", "bye");
    bool b2 = (*pf)("hello", "bye");
    bool b3 = lengthCompare("hello", "bye");

    //no conversion between pointers to one function type and
    //pointers to another function type
    pf = 0; // points to no function
    pf = sumLength; // error: return type differs
    pf = cstringCompare; // parameter differs
    pf = lengthCompare; // ok: function and pointer types match exactly.

    // pointers to Overloaded functions
    void (*pf1)(unsigned int) =ff; //points to the ff(unsigned)

    void (*pf2)(int) =ff; // error: no matching param list.
    double (*pf3)(int *) =ff; // error: return type doesn't match.


    return 0;
}