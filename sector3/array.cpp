//
// Created by fiberhome on 2020/11/18.
//
// array is a data structure that is similar to vector.
// difference: array has fixed size,
#include "iostream"
#include "array"
#include "string"

using namespace std;

int main() {
    // when declare an array, the dimension must be a const, that is must be known at compile time.
    unsigned cnt = 42;
    constexpr unsigned sz = 42;
    int arr[10];    //right
    int *parr[sz];  // array of 42 pointers to int
    string bad[cnt]; // error: cnt
//    string strs[get_size()];

//  The char arrays is special
    char a2[] = "C++";
    char a3[] = {'C', '+', '+', '\0'};
//   Both above have same size 4.
//    const char a4[6] = "abcdef"; // error: should remain a space to null \0.

//    can't copy an array to another.
//    int a[] = {1, 2, 3};
//    int a2[] = a; //error

//    array of pointers and references
    int *ptrs[10]; // array of ten pointers to int
//    if have parentheses, read from inside out, 1.inside 2. right 3. left.
    int (*parray)[10] = &arr; // Parray points to an array of ten ints.
    int (&arrRef)[10] = arr;    // refers to an array of ten ints.
    int *(&arry)[10] = ptrs;

    // count the number of grades by clusters of 0-9, .. .
    unsigned scores[11] = {};
    unsigned grade;
    while (cin >> grade) {
        if (grade <= 100)
            ++scores[grade / 10];
        else break;
    }

//    pointers to array support same operations as iterators
    int arra[] = {1, 2, 3};
    int *p = arra;
    ++p;    //point to arr[1]
    int *pbegin = begin(arra);
    int *pend = end(arra);

//    pointers to multi-dimensional array
    int ia[3][4];
    int (*pd)[4] = ia;
    pd = &ia[2];
    cout<<*pd[2]<<endl;

    return 0;
}