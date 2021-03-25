//
// Created by fiberhome on 2021/3/25.
//

#ifndef NOW_CODE_197_H
#define NOW_CODE_197_H

#include "string"
#include "iostream"
#include "memory"
#include "set"
#include "vector"

using namespace std;

// Local classes
// A class can be defined inside a function body. Such a class is called local class.

// Local class may not use variables from the function's scope
// local class can only access type names, static variables, and enumerators defined within the enclosing local scopes.

int a, val;

void foo(int val) {
    static int si;
    enum Loc {
        a = 1024, b
    };
    // Bar is local to foo
    struct Bar {
        Loc LocVal; // ok: uses a local type name
        int barVal;

        void fooBar(Loc l = a) {
            barVal = val;   // error: val is local to foo
            barVal = ::val; // ok: uses a global object
            barVal = si;    // ok: uses a static local object
            LocVal = b; // ok: uses an enumerator
        }
    };
}

// Normal Protection Rules Apply to Local Classes

// Name lookup within a local class

// Nested local class
void foo() {
    class Bar {
    public:
// ...
        class Nested; // declares class Nested
    };
// definition of Nested
    class Bar::Nested {
// ...
    };
}


#endif //NOW_CODE_197_H
