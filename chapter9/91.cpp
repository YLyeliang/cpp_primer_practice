//
// Created by fiberhome on 2021/1/8.
//

#include <deque>
#include <forward_list>
#include "vector"
#include "string"
#include "list"
#include "array"
#include "iostream"
#include "../chapter7/Sales_data.h"

using namespace std;

int main() {
    list<string>::iterator iter;
    vector<int>::difference_type count;

    list<string> a = {"haha", "hehe", "xixi"};
    auto it1 = a.begin(); // list<string>::iterator
    auto it2 = a.rbegin(); // list<string>::reverse_iterator
    auto it3 = a.cbegin(); // list<string>::const_iterator
    auto it4 = a.crbegin(); // list<string>::const_reverse_iterator

    // type is explicitly specified
    list<string>::iterator it5 = a.begin();
    list<string>::const_iterator it6 = a.begin();
    // iterator or const_type depending on a's type of a.
    auto it7 = a.begin(); // const_iterator only if a is const
    auto it8 = a.cbegin(); // it8 is const_iterator

// Defining and initializing container

    // each has 3 ele, initialized from given initializers.
    list<string> authors = {"Jessy", "Jessica", "Jack"};
    vector<const char *> article = {"a", "b", "c"};
    list<string> list2(authors); // copy: type match
    deque<string> authList(authors); // error: type not match
    vector<string> words(authors); // error: type not match

    // ok: convert type
    forward_list<string> words2(article.begin(), article.end());

    // copies up to but not including the element denoted by it
    auto it = authors.begin();
    it++;
    deque<string> authList2(authors.begin(), it);

    // Sequential Container Size-Related Constructors
    vector<int> ivec(10, -1); // ten, each to -1
    list<string> svec(10, "hi"); // ten, each "hi"
    forward_list<int> fvec(10); // ten elements, each initialized to 0
    deque<string> dvec(10); // ten, each empty

    // Library arrays Have Fixed Size
    array<int, 42>; // type is: array that holds 42 ints
    array<string, 10>; // ... 10 strings
    array<int, 10>::size_type i;
    array<int>::size_type j; // array<int> is not a type
    array<int, 10> ia1;
    array<int, 10> ia2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array<int, 10> ia3 = {42}; // ia3[0] is 42, remaining are 0

    // although cannoot copy or assign objects of built-in array types, it's ok on array
    int digs[5] = {0, 1, 2, 3, 4};
    int cpy[5] = digs; // error
    array<int, 5> digits = {0, 1, 2, 3, 4};
    array<int, 5> copys = digits; // ok

    list<string> names;
    vector<const char *> oldstyle;
    names = oldstyle; // error: type don't match
    // ok
    names.assign(oldstyle.cbegin(), oldstyle.cend());

    // relational operator
    vector<int> v1 = {1, 3, 5, 7, 9, 12};
    vector<int> v2 = {1, 3, 9};
    vector<int> v3 = {1, 3, 5, 7};
    vector<int> v4 = {1, 3, 5, 7, 9, 12};
    v1 < v2;  // true: the first unequal element, 5 < 9
    v1 < v3; // false;
    v1 == v4; // true
    v1 == v2; // false

// 9.3 Sequential container operation
    // Adding elements
    // push_back, push_front
    // insert (vecotr, deque, list, string): takes an iterator as first argument.
    list<string> slist = {"hehe"};
    vector<string> svector;
    auto slist_it = slist.begin();
    slist.insert(slist_it, "Hello"); //insert hello before iter
    // inserting a range of elements
    svector.insert(svector.end(), 10, "Anna");
    vector<string> v = {"a", "b", "c", "d"};
    // insert the last two elements of v at the beginning of slist
    slist.insert(slist.begin(), v.end() - 2, v.end());
    slist.insert(slist.end(), {"word", "go", "in", "the", "end"});
    //runtime error: iterators denoting the range to copy from
    // must not refer to the same container as the one we are changing
    slist.insert(slist.begin(), slist.begin(), slist.end()); //error

    // using return from insert
    list<string> lst;
    auto iter2 = lst.begin();
    string word;
    while (cin >> word)
        // return an iterator referring to this new element
        iter2 = lst.insert(iter2, word); // same as calling push_front

    // using emplace operation
    // emplace_front, emplace_back, emplace

    // construct a Sales_data object at the end of c
    // uses the three-argument Sales_data constructor.
    vector<Sales_data> c;
    c.emplace_back("23123", 25, 15.00);
    c.emplace(c.begin(), "12312");
    // error in push_back
    c.push_back("123", 25, 12.23);
    // ok, when create a temporary Sales_data object to pass to push_back.
    c.push_back(Sales_data("123", 124, 22.3));

    // Accessing Elements
    // c.back() c.front() c[n] c.at(n). All return a reference to specified index.
    if (!c.empty()) {
        // val and val2 are copies of the value of the first element in c
        auto val = *c.begin(), val2 = c.front();
        // val3 & val4 are .. last ..
        auto last = c.end();
        auto val3 = *(--last); // can't decrement forward_list iterators
        auto val4 = c.back(); // not supported by forward_list
    }

    // The access members return references
    vector<int> d = {1, 2, 3, 4, 5};
    if (!d.empty()) {
        d.front() = 42; // assign 42 to first element in d
        auto &v = d.back(); // get a reference to the last element
        v = 1024;
        auto v2 = d.back();
        v2 = 0; // no change to element in d
    }

    // Erasing element
    // pop_front pop_back clear()
    // erase(p) erase(b,e) return iterator
    while (!lst.empty()) {
        lst.pop_front();
    }

    // removing an element from within the container
    // erase odd element
    list<int> lst2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it_lst2 = lst2.begin();
    while (!lst2.empty()) {
        if (*it_lst2 % 2)
            lst2.erase(it_lst2);
        else
            ++it_lst2;
    }

    // removing multiple elements
    // erase(b,e) delete the range of elements between two iterators
    auto elem1 = slist.erase(slist.begin(), slist.end());
    slist.clear();// same as above

    // specialized forward_list operations
    // lst.before_begin(): Iterator denoting the nonexistent element before the beginning of the list
    // insert_after(p,t) inserts element(s) after the one denoted by iterator p. t is
    // insert_after(p,n,t) an object, n is a count, b and e are iterators denoting range
    // insert_after(p,b,e) il is a braced list. return iterator to the last inserted element.
    // insert_after(p,il)
    // emplace_after(p, args) use args to construct an element after the one denoted by iterator p.
    // erase_after(p)
    // erase_after(b,e)

    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto prev = flst.before_begin(); // "off the start" of the flst
    auto curr = flst.begin(); // the first element
    while (curr != flst.end()) {
        if (*curr % 2)
            curr = flst.erase_after(prev);
        else {
            prev = curr;
            ++curr;
        }
    }

    // Resizing a Container
    // If current size is larger than requested size, elements are deleted from the back of the container;
    // else added to the back.
    list<int> size_list(10, 42);
    size_list.resize(15); // add five elements of 0 to the back
    size_list.resize(25, -1); // adds ten of -1 ...
    size_list.resize(5); // erases 20 elements from the back.

    // container operations may invalidate iterators
    // it,pnt and ref to a vector or string are invalid if the containers are reallocated.
    // before the insertion, indirect ref are valid, those to elements after insertion are invalid

    // ... to a deque are invalid if we add elements anywhere but at the front or back.
    // if we add at the front or back, it are invalid, while ref and pnt are valid.

    // ... to a list or forward_list are valid.

    // writing loops that change a container
    // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements
    vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto vi_iter = vi.begin(); // call begin, not cbegin because we're changing vi
    while (vi_iter != vi.end()) {
        if (*vi_iter % 2) {
            vi_iter = vi.insert(vi_iter, *vi_iter); // duplicate the current element
            vi_iter += 2; // advance past this element and the one inserted before it
        } else
            vi_iter = vi.erase(vi_iter); // remove even elements
        // iter denotes the element after the one we erased
    }

    // avoid storing the iterator returned from end
    // disaster: the behavior of this loop is undefined.
    auto begin = vi.begin(), end = vi.end(); // bad idea, saving the value of the end iterator
    // insert the new value and reassign begin, which otherwise would be invalid.
    while (begin != end) {
        ++begin;
        begin = vi.insert(begin, 42);
        ++begin;
    }
    // We may get an infinite loop on many implementations.

    // rather than storing the end() iterator, we must recompute it after each insertion:
    // safer: recalculate end on each trip whenever the loop adds/erases elements

    while (begin != vi.end()) {
        ++begin;
        begin = vi.insert(begin, 42);
        ++begin;
    }



}