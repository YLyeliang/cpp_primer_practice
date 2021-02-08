
//
// Created by yel on 2021/2/8.
//

#ifndef NOW_CODE_135_H
#define NOW_CODE_135_H

#include "string"
#include "memory"

using namespace std;

// StrVec Class, will have three pointers into the space it uses for its elements:
// elements, which points to the first element in the allocated memory
// first_free, which points just after the last actual element
// cap, which points just past the end of the allocated memory

// in addition to these pointers, StrVec will have a member named alloc that is an allocator<string>. 4 functions:
// alloc_n_copy will allocate space and copy a given range of elements
// free will destroy the constructed elements and deallocate the space
// chk_n_alloc will ensure that there is room to add at least one more element to the StrVec
// reallocate will reallocate the StrVec when it runs out of space.

// simplified implementation of the memory allocation strategy for a vector-like class
class StrVec {
public:
    StrVec() :   // the allocator members is default initialized
            elements(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(const StrVec &);  // copy constructor
    StrVec &operator=(const StrVec &);   // copy assignment
    ~StrVec();  // destructor
    void push_back(const string &);  // copy the element
    size_t size() const { return first_free - elements; }

    size_t capacity() const { return cap - elements; }

    string *begin() const { return elements; }

    string *end() const { return first_free; }


private:
    std::allocator<string> alloc;

    // used by the function that add the elements to the StrVec
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }

    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<strin *, string *> alloc_n_copy
            (const string *, const string *);

    void free();    // destroy the elements and free the space
    void reallocate();  // get more space and copy the existing elements
    string *elements;   // pointer to the first element in the array
    string *first_free; // pointer to the first free element in the array
    string *cap;    // pointer to one past the end of the array


};

void StrVec::push_back(const string &s) {
    chk_n_alloc();  // ensure that there is room for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

// The alloc_n_copy Member
pair<string *, string *>
StrVec::alloc_n_copy(const string *b, const string *e) {
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e - b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // may not pass deallocate a 0 pointer; if element is 0, there's no work to do
    if (elements) {
        // destroy the old elements in reverse order
        for (auto p = first_free; p != elements;/* empty*/)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

// copy-control Members
StrVec::StrVec(const StrVec &s) {
    // call alloc_n_copy to allocate exactly as many elements as in s
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements=newdata.fir
}

#endif //NOW_CODE_135_H