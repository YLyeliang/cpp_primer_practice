
//
// Created by yel on 2021/2/8.
//

#ifndef NOW_CODE_135_H
#define NOW_CODE_135_H

#include "string"
#include "memory"
#include "utility"

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

void StrVec::push_back(const string &s) {
    chk_n_alloc();  // ensure that there is room for another element
    // construct a copy of s in the element to which first_free points
    alloc.construct(first_free++, s);
}

void StrVec::push_back(string &&s) {
    chk_n_alloc();  // reallocates the StrVec if necessary
    alloc.construct(first_free++, std::move(s));
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
    elements = newdata.first;
    first_free = cap = newdata.second;
}

// The destructor calls free
StrVec::~StrVec() { free(); }

// copy-assignment operator
StrVec &Strvec::operator=(const StrVec &rhs) {
    // call alloc_n_copy to allocate exactly as many elements as in the rhs
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    // like the copy constructor
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

// Moving, not copying, elements during reallocation

// before we write the reallocate member,  we should think a bit about what it must do.
// 1. Allocate for a new, larger array of strings
// 2. Construct the first part of that space to hold the existing elements
// 3. Destroy the elements in the existing memory and deallocate that memory

// move constructor, std::move

// The reallocate Member
// we'll start by calling allocate to allocate new space. We'll double the capacity of the StrVec each time we reallocate
void StrVec::reallocate() {
    // we'll allocate space for twice as many elements as current size
    auto newcapacity = size() ? 2 * size() : 1;
    // allocate new memory
    auto newdata = alloc.allocate(newcapacity);
    // move the data from the old memory to the new
    auto dest = newdata;    // points to the next free position in the new array
    auto elem = elements;   // points to the next element in the old array
    for (size_t i = 0; i != size(); i++)
        alloc.construct(dest++, std::move(*elem++));
    free(); // free the old space once we've moved the elements
    // update our data structure to points to the new elements
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

// move
StrVec::StrVec(StrVec &&s) noexcept // move won't throw any exceptions
// member initializes take over the resources in s
        : elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // after move, the s will be destoryed
    // leave s in a state in which it's safe to run destructor
    s.elements = s.first_free = s.cap = nullptr;
}

// Move operations, Library Containers, and Exceptions

// move assignment
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    // direct test for self-assignment
    if (this != &rhs) {
        free(); // free existing elements
        elements = rhs.elements;    // take over the resources from rhs
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.cap = rhs.first_free = nullptr;
    }
    return *this;
}
// warning: after a move operation, the "moved-from" object must remain a valid, destructible objet

// 144 Assignment Operator
StrVec &StrVec::operator=(initializer_list<string> il) {
    // alloc_n_copy allocates space and copies elements from given range
    auto data = alloc_n_copy(il.begin(), il.end());
    free(); // destroy the elements in this object and free the space
    elements = data.first;    // update data members to point to the new space
    first_free = cap = data.second;
    return *this
}

#endif //NOW_CODE_135_H
