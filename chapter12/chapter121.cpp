//
// Created by yel on 2021/1/24.
//

#include "iostream"
#include "memory"
#include "list"
#include "vector"

using namespace std;


int main() {

    // Dynamic memory and Smart Pointers
    // dynamic memory: new and delete
    // Smart Pointers: shared_ptr, which allows multiple pointers to refer to the same object
    // unique_ptr, which "owns" the object to which it points.
    // weak_ptr that is a weak reference to an object managed by shared_ptr. All three are defined in memory header.

    // shared_ptr
    shared_ptr<string> p1; // shared_ptr that can point at a string
    shared_ptr<list<int>> p2; // ... list of int
    // default pointers holds a null pointer
    // if p1 is not null, check whether it's an empty string. p1 true if it points to an object
    if (p1 && p1->empty())
        *p1 = "Hi";

    // make_shared
    // This function allocate and initializes an object in dynamic memory and returns a shared_ptr that
    // points to that object.
    shared_ptr<int> p3 = make_shared<int>(42); // shared_ptr that points to an int with value 42.
    shared_ptr<string> p4 = make_shared<string>(10, '9'); // ... string with value 9999999999
    shared_ptr<int> p5 = make_shared<int>(); // p5 points to an int that is initialized to 0

    auto p6 = make_shared<vector<string>>(); // p6 points to an dynamically allocated, empty vector<string>.
    auto p = make_shared<int>(42);
    auto q(p); // copy

    // Once a shared_ptr's Counter goes to zero, it automatically free the object it manages.
    auto r = make_shared<int>(42);
    r = q;  // assign to r, making it points to a different address.
    // increase the use count for the object to which q points.
    // reduce the use count of the object to which r had pointed.
    // the object r had pointed to has no users; that object is automatically freed

    // shared_ptr automatically destroy their objects ...
    // ... and automatically free the associated memory

    shared_ptr<Foo> factory(T arg) {
        // process arg as appropriate
        // shared_ptr will take care of deleting this memory
        return make_shared<Foo>(arg);
    }

    void use_factory(T arg) {
        shared_ptr<Foo> p = factory(arg);
        // use p
    } // p goes out of scope; the memory to which p points is automatically freed

    // The memory will not be freed if there is any other shared_ptr pointing to it
    shared_ptr<Foo> use_factory(T arg) {
        shared_ptr<Foo> p = factory(arg);
        return p; // reference count is incremented when we return p
    } // p goes out of scope; the memory to which p points is not freed


}