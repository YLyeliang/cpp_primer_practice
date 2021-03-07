//
// Created by yel on 2021/3/7.
//

#ifndef CPP_PRIMER_PRACTICE_164_H
#define CPP_PRIMER_PRACTICE_164_H

#include "string"
#include "iostream"
#include "memory"
#include "utility"
#include "sstream"

using namespace std;

// xxx is a template function or class that can take a varying number of parameters
// varying params are known as a parameter pack
// two kinds: template parameter pack, function xxx
// use an ellipsis(...) to indicate a pack.

// Args is a template parameter pack; rest is a function parameter pack
// Args represents zero or more template type parameters
// rest ... function parameters
template<typename T, typename ... Args>
void foo(const T &t, const Args &... rest);
// see example 1

// The sizeof... Operator
// use it to know the number of elements in pack
template<typename ...Args>
void g(Args... args) {
    cout << sizeof...(Args) << endl;
    cout << sizeof...(args) << endl;
}

// 164.1 Writing a variadic function template
// in chapter 6.2, it's said that initializer_list can be used to take varying number of arguments.
// However, this must be the same type
// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template<typename T>
ostream &print(ostream &os, const T &t) {
    return os << t;
}

// this version will be called for all but the last element in the pack
template<typename T, typename ... Args>
ostream &print(ostream &os, const T &t, const Args &... rest) {
    os << t << ", ";
    return print(os, rest...);   // recursive call; print the other arguments
}

// 164.2 Pack Expansion
// trigger an expansion by putting an ellipsis(...) to the right of the pattern
//template<typename T, typename ... Args>
//ostream &print(ostream &os, const T &t, const Args &... rest)  // expand Args
//{
//    os << t << ", ";
//    return print(os, rest...);
//}

// Understanding Pack expansions
// call debug_rep on each argument in the call to print
template<typename T>
string debug_rep(const T &t) {
    ostringstream ret;
    ret << t;   // uses T's output operator to print a representation of t
    return ret.str();   // return a copy of the string to which the return bound.
}

template<typename ... Args>
ostream &errorMsg(ostream &os, const Args &... rest) {
    return print(os, debug_rep(rest)...);
}
// while print(os,debug_rep(rest...)) would fail to compile
// see example 2

// 164.3 Forwarding parameter packs
// we can use variadic templates with forward to write functions that pass their arguments unchanged to some other function.
// we'll add an emplace_back member to the StrVec(13.5)
class StrVec {
public:
    template<class... Args>
    void emplace_back(Args &&...);

    // remaining members as in 13.5
    std::string &operator[](std::size_t n) { return elements[n]; }

    const std::string &operator[](std::size_t n) const { return elements[n]; }

    StrVec &operator=(std::initializer_list<std::string>);  // see 144

    StrVec() :   // the allocator members is default initialized
            elements(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(StrVec &&) noexcept;  // move constructor
    StrVec &operator=(StrVec &&);   // move assignment
    StrVec(const StrVec &);  // copy constructor
    StrVec &operator=(const StrVec &);   // copy assignment
    ~StrVec();  // destructor
    void push_back(const string &);  // copy the element
    void push_back(string &&);  // move the element 136
    size_t size() const { return first_free - elements; }

    size_t capacity() const { return cap - elements; }

    string *begin() const { return elements; }

    string *end() const { return first_free; }


private:
    std::allocator<string> alloc;

    // used by the function that add the elements to the StrVec
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }

    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<string *, string *> alloc_n_copy
            (const string *, const string *);

    void free();    // destroy the elements and free the space
    void reallocate();  // get more space and copy the existing elements
    string *elements;   // pointer to the first element in the array
    string *first_free; // pointer to the first free element in the array
    string *cap;    // pointer to one past the end of the array
};

template<class...Args>
void StrVec::emplace_back(Args &&...args) {
    chk_n_alloc();  // reallocates the StrVec if necessary
    alloc.construct(first_free++, std::forward<Args>(args)...);
}
// chk_n_alloc to ensure that there is enough room
// The expansion in the call: std::forward<Args>(args)... expands both template and func pack
// generates with the form: std::forward<Ti>(ti)
// Ti is tht ith in the template pack
// see example 3



#endif //CPP_PRIMER_PRACTICE_164_H
