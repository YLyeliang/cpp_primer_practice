//
// Created by fiberhome on 2021/1/19.
//
#include "iostream"
#include "vector"
#include "algorithm"
#include "list"
#include "fstream"
#include "numeric"
#include "../Sales_data.h"


using namespace std;

int main() {
    // 10.4 Revisiting Iterators
    // insert iterators: bound to a container and can be used to insert elements into the container.
    // Stream iterators: bound to input or output streams and ... iterate through the associated IO stream
    // Reverse iterators: move backward, rather than forward.
    // Move iterators: move rather than copy their elements

    // insert iterators
    list<int> lst = {1, 2, 3, 4};
    list<int> lst2, lst3; // empty lists
    copy(lst.cbegin(), lst.cend(), front_inserter(lst2)); // lst2: 4 3 2 1
    copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin())); // lst3: 1 2 3 4

    // iostream iterators
    // istream_iterator ostream_iterator
    // operations on istream_iterators
    istream_iterator<int> init_it(cin);  // reads ints from cin
    istream_iterator<int> int_eof; // end iterator value
    ifstream in("file");
    istream_iterator<string> str_it(in); // reads string from "file"

    vector<int> vec;
    istream_iterator<int> eof; // istream 'end' iterator
    while (init_it != eof)
        vec.push_back(*init_it++);

    // more useful rewrite
    istream_iterator<int> in_iter(cin);
//    vector<int> vec(in_iter, eof);

    // using stream iterator with the algorithms
    cout << accumulate(in_iter, eof, 0) << endl;

    // operations on ostream_iterators
    ostream_iterator<int> out_iter(cout, " ");
    for (auto e: vec)
        *out_iter++ = e; // writes this element to cout
    //out_iter++=e; equal to above
    cout << endl;
    // a more easier way is copy fucntion
    copy(vec.begin(), vec.end(), out_iter);
    cout << endl;

    // using stream iterators with class type
    istream_iterator<Sales_data> item_iter(cin);
    // store the first transaction in sum and read the next record
    Sales_data sum = *item_iter++;
    while (item_iter != eof) {
        if (item_iter->bookNo == sum.bookNo)
            sum += *item_iter++;
        else {
            out_iter = sum; // write current sume
            sum = *item_iter++; // read the next transaction
        }
    }

    // Reverse iterator
    // rbegin, rend, rcbegin, rcend()

    // The iterator Categories   Five
    // Input iterators: can read elements in sequence. must provide
    // == != to compare two iterators
    // prefix and postfix increment ++
    // Dereference operator * to read an element;
    // Arrow operator -> as a synonym for (*it).member
    // example: find   accumulate require input iterators; istream_operator are input iterators

    // Output iterators: can be thought of as having complementary function to input iterators; must provide
    // ++
    // *

    // Forward iterators: can read and write a given sequence.
    // Bidirectional iterators: can read and write a sequence forward or backward.

    // Random-access iterators: provide constant-time access to any position in the sequence. provide
    // relational operators < <= > >=.  addition and subtraction  + += - -=
    // subscript operator iter[n] as a synonym for *(iter+n)

// 10.5.2 Algorithm Parameter Patterns
    // Most of the algorithms have one of the following four forms:
    // alg(beg,end,args);
    // alg(beg,end,dest,other args);
    // alg(beg,end,beg2,other args);
    // alg(beg,end, beg2,end2,other args);

// 10.5.3 Algorithm Naming Conventions
    // reverse reverse_copy remove_if remove_copy_if.   _if & _copy version.

// 10.6 Container Specific Algorithms



}