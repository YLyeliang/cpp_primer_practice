//
// Created by fiberhome on 2021/3/19.
//
#include "string"
#include "iostream"
#include "memory"

using namespace std;
// 19. Specialized Tools and Techniques
// In this chapter we look at some of the less-commonly used features in the
// language.

// 191. Controlling Memory Allocation

// example 1
void *operator new(size_t size) {
    if (void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}

void operator delete(void *mem) noexcept { free(mem); }


int main() {
    // 191.1 Overloading new and delete
    // to know a bit more about how new and delete expression works
    string *sp = new string("a value"); // allocate and initialize a string
    string *arr = new string[10];   // allocate ten default initialized strings
    // three steps:
    // 1. expression calls a library function named operator new to allocate raw, untyped memory large enough to hold
    // 2. runs the appropriate constructor
    // 3. a pointer to a newly allocated and constructed object is returned

    // delete
    delete sp;
    delete[] arr;
    // two step:
    // 1. destructor runs on the object
    // 2. frees the memory by calling library function named operator delete

    // The operator new and operator delete Interface
    // The library defines 8 overloaded versions of operator new and delete functions.
    // these versions might throw an exception
    void *operator new(size_t); // allocate an object
    void *operator new[](size_t); // allocate an array
    void *operator delete(void *) noexcept; // free an object
    void *operator delete[](void *) noexcept; // free an array
    // versions that promise not to throw; see § 12.1.2 (p. 460)
    void *operator new(size_t, nothrow_t &) noexcept;
    void *operator new[](size_t, nothrow_t &) noexcept;
    void *operator delete(void *, nothrow_t &) noexcept;
    void *operator delete[](void *, nothrow_t &) noexcept;

    // The malloc and free Functions
    // malloc takes a size_t that says how many bytes to allocate. It returns a pointer to the memory that it allocated,
    // or 0 if it was unable to allocate the memory.
    // free takes a void* that is a copy of a pointer that was returned from malloc
    // a simple way to see example 1

    // 191.2 Placement new Expressions
    // new (place_address) type
    // new (place_address) type (initializers)
    // new (place_address) type [size]
    // new (place_address) type [size] { braced initializer list }

    // Explicit destructor invocation
    sp->~string();

}

