//
// Created by fiberhome on 2020/12/4.
//

#include "iostream"
#include "string"
#include "vector"
#include "cassert"

using namespace std;

// default arguments
typedef string::size_type sz;

// inline function, meant to optimize small, straight-line functions that
// are called frequently.
// not inline recursive function, more than 75-line will surely not be expanded.
inline string screen(sz ht = 24, sz wd = 80, char background = ' ');

// constexpr
constexpr int new_sz() { return 42; }

constexpr int foo = new_sz(); // ok

// constexpr permitted to return a value that is not a constant:
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }


int main() {
    return 0;


}

// the declaration of wd, def, and ht must appear outside a function.
