//
// Created by fiberhome on 2021/2/1.
//

#include "string"
#include "iostream"
#include "memory"
#include "list"
#include "vector"
#include "string"

using namespace std;

int main() {
//    int *pia = new int[get_size()]; // pia points to the first of these ints

    typedef int arrT[42]; // arrT names the type array of 42 ints
    int *p = new arrT;

    // Allocating an array yields a pointer to the element type
    // we get an pointer to the element type of the array instead of an object with an array type.
    // so, range for and begin/end are not used

    // initializing an array of dynamically allocated objects
    int *pia1 = new int[10];
    int *pia2 = new int[10]();  // block of ten ints value initialized to 0
    string *psa = new string[10]; // block of ten empty string
    string *psa2 = new string[10](); // save as above

    int *pia3 = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    string *psa3 = new string[10]{"a", "an", "the", string(3, 'X')};

    // it is legal to dynamically allocate an empty array
    size_t n = 10; // get_size returns the number of elements needed
    int *p1 = new int[n];
    for (int *q = p1; q != p1 + n; ++q)
        /* process the array*/;
    // If get_size() returns 0, the code works fine.
    char arr[0]; // error: cannot define a zero-length array
    char *cp = new char[0]; // ok: but cp can't be dereferenced

    // Freeing Dynamic Arrays
    delete p; // p must point to a dynamically allocated object or null
    delete[]pia1; // pa must point to a dynamically allocated array or null

    // Smart pointers and dynamic arrays
    // up points to an array of ten uninitialized ints
    unique_ptr<int[]> up(new int[10]);

    // unique_ptr to arrays operations
    // unique_ptr<T[]> u
    // unique_ptr<T[]> u(p)
    // u[i]     Returns the object at position i in the array that u owns
    for (size_t i = 0; i != 10; ++i) {
        up[i] = i;
    }
    up.release(); // automatically uses delete[] to destroy its pointer

    // shared_ptr provide no direct support for managing a dynamic array
    // we must provide our own delete
    shared_ptr<int> sp(new int[10], [](const int *tmp) { delete[] tmp; });

    // shared_ptr does not directly support managing arrays affect how we access the elements in the array
    for (size_t i = 0; i != 10; ++i)
        *(sp.get() + i) = i; // use get to get a built-in pointer
    sp.reset();

    // The allocator class
    // allocator<T> a
    // a.allocate(n)    Allocate raw, unconstructed memory ot hold n objects of type T.
    // a.deallocate(p,n)
    // a.construct(p, args)
    // a.destroy(p)
    allocator<string> alloc;
    auto const ps = alloc.allocate(n); //allocate n unconstructed strings

    // allocators allocate unconstructed memory
    auto qq = ps; // q will point to one past the end constructed element
    alloc.construct(qq++); // *qq is the empty string
    alloc.construct(qq++, 10, 'c'); // *qq is ccccccc
    auto s_tmp = *qq;
    alloc.construct(qq++, "hi");    // *qq is hi

    // When we're finished using the objects, we must destroy the elements we constructed
    while (qq != ps)
        alloc.destroy(--qq);

    // once the elements have been destroyed, we can either reuse  the memory or return the memory to the system.
    // free by below
    alloc.deallocate(ps, n);

    // Algorithms to copy and fill uninitialized Memory

    // as a companion to the allocator class, library defines two algorithms that can construct objects in uninitialized
    // memory, defined in memory header
    // uninitialized_copy(b, e, b2)     copies elements from the input range denoted by iterators b and e into
    //              unconstructed, raw memory denoted by the iterator b2.
    // uninitialized_copy_n(b, n, b2)   copies n elements starting from the one denoted by iterator b
    // uninitialized_fill(b, e, t)  constructs objects in the range of raw memory denoted by iterators b and e as a copy
    //              of t
    // uninitialized_fill_n(b, n, t) ...

    

    return 0;


}