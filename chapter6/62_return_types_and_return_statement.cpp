//
// Created by fiberhome on 2020/12/1.
//

#include "iostream"
#include "string"

using namespace std;

// two forms of return statements;
// return;
// return expression;


// when use return in void function. The return is analogous to the break statement.
void swap(int &v1, int &v2) {
    if (v1 == v2)
        return;
    int tmp = v2;
    v2 = v1;
    v1 = tmp;
}

// reference Returns are lvalues
char &get_val(string &str, string::size_type ix) {
    return str[ix];
}

// returning a pointer to an array
// since array cannot be copied, a function cannot return an array.
// with alias.
typedef int arrT[10];
using arrT = int[10]; // equivalent to above.
arrT *func(int i); // func return a pointet to an array of ten ints.

// declaring a func that returns a pointer to an array. without alias.
//Type (*function(param_list ))[dimension]
int (*func(int i))[10];

// using a trailing return type
auto func(int i) -> int (*)[10]; // return a pointer to an array of ten ints.

// using decltype
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

decltype(odd) *arrPtr(int i) {
    return (i % 2)? &odd : &even
}


int main() {

    // 1. reference returns are lvalues.
//    string s("a value");
//    cout << s << endl;
//    get_val(s, 0) = 'A';
//    cout << s << endl;


    return 0;

}