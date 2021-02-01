//
// Created by yel on 2021/1/24.
//
#include "string"
#include "iostream"
#include "memory"
#include "list"
#include "vector"
#include "string"


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

    vector<string> v1;
    {// new scope
        vector<string> v2 = {"a", "an", "the"};
        v1 = v2; // copy
    } // v2 is destroyed
    // v1 has three elements, which are copies of the ones originally in v2

    // Managing Memory Directly
    // The new operator allocates memory, and delete free memory allocated by new.
    // As a result, programs that use
    //smart pointers are likely to be easier to write and debug.

    // using new to Dynamically Allocate and Initialize Objects

    // new returns a pointer to the object it allocates

    // default, dynamically allocated objects are default initialized, which means that objects of built-in
    // or compound type have undefined value; objects of classes type are initialized by their default constructor.
    int *pi = new int; // pi points to a dynamically allocated, unnamed uninitialized int

    auto *ps = new string; // initialized to empty string

    // using direct initialization
    int *pi2 = new int(1024); // object to which pi2 points has value 1024
    string *ps2 = new string(10, "9"); // *ps2 is "00000000"
    vector<int> *pv = new vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8};

    string *ps3 = new string(); // initialized to empty string
    int *pi1 = new int; // default initialized, undefined
    int *pi3 = new int(); // value initialized to 0, *pi2 is 0

    auto p1 = new auto(obj); // p points to an object of type of obj that object is initialized from obj
    auto p2 = new auto{a, b, c}; // error: must be parenthese for the initializer.

    // Dynamically Allocated const Objects
    const int *pci = new const int(1024);
    const string *pcs = new const string;

    // Memory Exhaustion
    // if new is unable to allocate the requested storage, it throws an exception of type bad_alloc
    int *p11 = new int;
    int *p12 = new(nothrow) int; // if allocation fails, new returns a null pointer

    // Freeing Dynamic Memory
    delete pi;

    // Pointer Values and delete

    int i, *pi21 = &i, *pi22 = nullptr;
    double *pd = new double(33), *pd2 = pd;
    delete i; // error: i is not a pointer
    delete pi21; // undefined: pi21 refers to local
    delete pd;  // ok
    delete pd2; // undefined: the memory pointed to by pd2 was already freed
    delete pi22; // ok: it is always ok to delete a null pointer

    const int *pci1 = new const int(1024);
    delete pci1; // ok: delete a const object

    // 3 common problems with using new and delete to manage dynamic memory:
    // 1. Forgetting to delete memory, which is known as "memory leak".
    // 2. Using an object after it has been deleted.
    // 3. Deleting the same memory twice.

    // Resetting the Value of a Pointer after a delete...
    // ...Provides Only Limited Protection

    // A fundamental problem with dynamic memory is that there can be several pointers
    // that point to the same memory.
    int *p21(new int(42)); // p points to dynamic memory
    auto q21 = p21; // p and q point to the same memory
    delete p21; // invalidates both p and q
    p21 = nullptr; // indicates that p is no longer bound to an object

    // 12.1.3 Using shared_ptrs with new
    // As we've seen, if we don't initialize a smart pointer, it is initialized as a null ptr.
    shared_ptr<double> p31;
    shared_ptr<int> p32(new int(42));

    // The smart pointer constructors that take pointers are explicit. Hence, we cannot implicitly
    // convert a built-in ptr to a smart ptr
    shared_ptr<int> p41 = new int(42); // error: must use direct initialization
    shared_ptr<int> p42(new int(42)); // ok

    // Don't mix Ordinary ptr and smart ptr...

    // Don't use /get to Initialize or Assign Another Smart Pointer
    shared_ptr<int> p51(new int(42)); // reference count is 1
    int *q51 = p51.get(); // ok: but don't use q in any way that might delete its pointer
    {// new block
        // undefined: two independent shared_ptr points to the same memory
        shared_ptr<int>(q51);
    } // block ends, q is destroyed, and the memory to which q points is freed
    int foo = *p51; // undefined; the memory to which p points is freed.

    // other shared_ptr operations
    p51 = new int(52); // error: cannot assign a pointer to a shared_ptr
    p51.reset(new int(1024)); // ok: p points to a new object
    if (!p51.unique())
        p51.reset(new string(*p)); // we aren't alone; allocate a new copy
    *p += newVal; // now that we know we're the only pointer, okay to change this object

    // 12.1.4 Smart Pointers and Exceptions

    // Smart Pointers and Dumb classes
    // Imagine using a network library
    struct destination; // represents what we are connect to
    struct connection; // // information needed to use the connection
    connection connect(destination *); // open the connection
    void disconnect(connection); // close the given connection
    void f(destination &d /*other parameters*/) {
        // get a connection; must remember to close it when done
        connection c = connect(&d);
        // use the connection
        // if we forget to call disconnect before exiting f, there will be no way to close c
    }
    // If connection has a destructor, that would automatically close the connection when f completes

    // Using our own deletion code
    // To use shared_ptr to manage a connection, we must first define a function to use in place of delete
    void end_connection(connection p) { disconnect(p); }
    void f(destination &d, /*other parameters*/) {
        connection c = connect(&d);
        shared_ptr<connection> p(&c, end_connection);
        // use the connection
        // when f exit, even if by an exception, the connection will be properly closed
    }

    // unique_ptr
    // A unique_ptr "owns" the object to which it points. Only one unique_ptr at a time can point to a given object.
    // The object to which a unique_ptr points is destroyed when unique_ptr is destroyed
    // operations
    // unique_ptr<T> u1
    // unique_ptr<T,D> u2     use delete to free its pointer, u2 will use a callable object of type D to free its pointer.
    // unique_ptr<T,D> u(d)
    // u = nullptr
    // u.release()
    // u.reset()
    // u.reset(q)
    // u.reset(nullptr)
    unique_ptr<double> p61;
    unique_ptr<int> p62(new int(42));

    // we can't copy or assign an unique_ptr
    unique_ptr<string> p63(new string("haha"));
    unique_ptr<string> p64(p63); // error: no copy for unique_ptr
    unique_ptr<string> p65;
    p65 = p64; // error: no assign for unique_ptr

    // transfers ownership from p63 to p64
    unique_ptr<string> p644(p63.release()); // release make p63 null
    unique_ptr<string> p66(new string("text"));
    // transfer ownership from p66 to p64
    p644.reset(p66.release()); // reset deletes the memory to which p644 had pointed

    // if we don't use another smart ptr to hold the pointer returned from release, our program take over responsibility
    // for freeing that resource
    p62.release(); // wrong: p62 won't free the memory and we've lost the pointer
    auto pp = p62.release(); // ok, but we must remember to delete(pp)

    // passing and Returning unique_ptrs
    unique_ptr<int> clone(int p) {
        // ok: explicitly create a unique_ptr from int*
        return unique_ptr<int>(new int(p));
    }
    // alternatively, we can also return a copy of a local object
    unique_ptr<int> clone(int p) {
        unique_ptr<int> q(new int(p));
        return q;
    }

    // passing a deleter to unique_ptr
    unique_ptr<objT, delT> ppp(new objT, fcn); // it will call an object named fcn of type delT

    // example
    void f(destination &d /*other parameters*/) {
        connection c = connect(d);
        // when p is destroyed, the connection will be closed
        unique_ptr<connection, decltype(end_connection) *> p(&c, end_connection);
        // ...
    }

    // 12.1.6 weak_ptr
    // is a smart ptr that doesn't control the lifetime of the object to which it points.
    // Instead, a weak_ptr points to the object managed by shared_ptr.
    // Binding the weak_ptr to a shared_ptr doesn't change the reference count of shared_ptr.
    // once the last shared_ptr pointing to the object goes away, the object itself will be deleted, even if weak_ptr point

    // operations
    // weak_ptr<T> w
    // weak_ptr<T> w(sp)
    // w = p
    // w.reset()
    // w.use_count() The number of shared_ptr that share ownership with w
    // w.expired()   Return true if w.use_count() is zero, false otherwise
    // w.lock()     If expired() is true, return a null shared_ptr, otherwise returns a shared_ptr to the object to which w points.

    // when we create weak_ptr, we initialize it from shared_ptr
    auto p7 = make_shared<int>(42);
    weak_ptr<int> wp(p7); // wp weakly shares with p; use count in p is unchanged.

    if (shared_ptr<int> np = wp.lock()) { // true if np is not null
        // inside the if, np shares its object with p
    }





}

// For same reason in 12.1.3. a function that returns a shared_ptr cannot implicitly convert a
// plain ptr in its return statement.
shared_ptr<int> clone(int p) {
    return new int(p); // error
}

shared_ptr<int> clone2(int p) {
    return shared_ptr<int>(new int(p));
}

// Consider the following function that operates on a shared_ptr:
// ptr is created and initialized when process is called
void process(shared_ptr<int> ptr) {
    // use ptr
} // ptr goes out of scope and is destroyed
// Copying a shared_ptr increments its reference count. Thus, inside process the count is at least 2.
// When process completes, the reference count of ptr is decrement but cannot go to zero.
// Therefore, when the local variable ptr is destroyed, the memory to which ptr points will not be deleted.

// The right way
shared_ptr<int> p(new int(42)); // reference count 1
proces(p); // copying p ++, in process the reference count is 2
int i = *p; // ok : reference count is 1


// Dynamic memory managed through built-in pointers (rather than
//smart pointers) exists until it is explicitly freed.
Foo *factory(T arg) {
    // process arg as appropriate
    return new Foo(arg); // caller is responsible for deleting this memory
}

void use_factory(T arg) {
    Foo *p = factory(arg);
    // use p but do not delete it
} // p goes out of scope, but the memory to which p points is not freed !

// to fix that
void use_factory(T arg) {
    Foo *p = factory(arg);
    // use p
    delete p; // remember to free the memory now that we no longer need it
}

// or, if other code needs to use the object allocated by use_factory, we should change that
// function to return a pointer to the memory it allocated
Foo *use_factory(T arg) {
    Foo *p = factory(arg);
    // use p
    return p; // caller must delete the memory
}

