//
// Created by yel on 2021/2/28.
//
#include<vector>
#include "string"
#include "iostream"
#include "memory"

using namespace std;
// Defining a Template

// Imagine that we want to write a compare function. We may define several such functions, each of which will compare
// values of  a given type.
// int compare(string,string)       int compare(double,double)

// Function Templates
// Rather than defining a new function for each type, we can define a function template.
// The template version of compare looks like
template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

// A template definition starts with the keyword template followed by a template parameter list,
// which is a comma-separated list of one or more template parameters bracketed by the < and > tokens

// Instantiating a Function Template
// When we call a function template, the compiler uses the arguments of the call to deduce the template arguments for us.
// see example 1

// Template Type Parameters
// ok: same type used for the return type and parameter
template<typename T>
T foo(T *p) {
    T tmp = *p;  // tmp will have the type to which p points
    // ...
    return tmp;
}

// error: must precede U with either typename or class
template<typename T, U>
calc(const T &, const U &);

// ok: ok: no distinction between typename and class in a template parameter list
template<typename T, class U>
c2(const T &, const U &);

// Nontype Template Parameters
// A nontype parameter represents a value rather than a type.
template<unsigned N, unsigned M>
int compare2(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
}
// see example 2

// inline and constexpr function templates
// ok: inline specifier follows the template parameter list
template<typename T>
inline T min(const T &, const T &);
// error: incorrect placement of the inline specifier
// inline template<typename T>
// T min(const T&,const T&);

// writing Type-independent code
// The compare function illustrates two important principles for writing generic code
// 1. The function parameters in template are reference to const
// 2. The tests in the body use only < comparisons, which may reduce the requirements of supported operations.
// Definitions of function templates and member functions of class templates are ordinarily put into header files.

// Compilation Errors are mostly reported during Instantiation
// consider the code below:
// Sales_data data1,data2;
// compare(data1,data2)
// it would be an error, since Sales_data have no < operator.
// This error cannot be detected until the compiler instantiates the definition of compare on type Sales_data

// 161.2 Class Template
// the compiler cannot deduce the template parameter type(s) for a class template.

// Defining a class template
// As an example, we'll implement a template version of StrBlob in chapter 12.1
template<typename T>
class Blob {
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;

    // constructors
    Blob();

    Blob(initializer_list<T> il);

    // number of elements in the Blob
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const T &t) { data->push_back(t); }

    // move version , see 136.3
    void push_back(T &&t) { data->push_back(std::move(t)); }

    void pop_back();

    // element access
    T &back();

    T &operator[](size_type i); // defined in 145
private:
    shared_ptr<vector<T>> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const string &msg) const;
};

// Instantiate a class template
// when we use a class template, we must supply extra information. It's a list of explicit template arguments
// that are bound to the template's parameters.
// see example 3, it's equivalent to
//template<>
//class Blob<int> {
//    typedef typename vector<int>::size_type size_type;
//
//    Blob();
//
//    Blob(initializer_list<int> il);
//
//    // ...
//    int &operator[](size_type i);
//
//private:
//    shared_ptr<vector<int>> data;
//
//    void check(size_type i, const string &msg) const;
//};

// Reference to a template type in the scope of the template

// Member functions of class templates
// when we define a member, the template arguments are the same as the template parameters.
// example
//ret-type StrBlob:member-name(parm_list)
// the corresponding Blob member will look like
//template<typename T>
//ret-type Blob<T>::member-name(parm_list)

// The check and Element Access Members
template<typename T>
void Blob<T>::check(size_type i, const string &msg) const {
    if (i >= data->size())
        throw out_of_range(msg);
}

template<typename T>
T &Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T &Blob<T>::operator[](size_type i) {
    // if i is too big, check will throw, preventing access to a nonexistent element
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

// Blob Constructors
template<typename T>
Blob<T>::Blob():data(make_shared<vector<T>>()) {}

template<typename T>
Blob<T>::Blob(initializer_list<T> il):data(make_shared<vector<T>>(il)) {}
// To use this constructor, we must pass an initializer_list in which the elements are compatible with the element type
// of the Blob
// see example 4
// If a member function is not used, it is not instantiated.


// Instantiation of class-template member functions
// By default, a member function of a class template is instantiated only if the program uses that member function.
// see example 5

// Simplifying Use of a Template class inside class code
// There's one exception that we must supply template arguments when we use a class template type
// BlobPtr throws an exception on attempts to access a nonexistent element
template<typename T>
class BlobPtr {
public:
    BlobPtr() : curr(0) {}

    BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    T &operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];  // (*p) is the vector to which this object points
    }

    // increment and decrement
    BlobPtr &operator++();  // prefix operators
    BlobPtr &operator--();

    BlobPtr operator++(int);

private:
    // check returns a shared_ptr to the vector if the check succeeds
    shared_ptr<vector<T>> check(size_t, const string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    weak_ptr<vector<T>> wptr;
    size_t curr;    // current position within the array
};
// We used BlobPtr&, not BlobPtr<T>&. Inside the scope of a class template, the compiler treats the reference to
// the template itself as if we supplied template arguments matching the template's parameters.

// Using a Class Template Name outside the Class Template Body
// Since outside the scope of the class, we must specify that the return type returns a BlobPtr instantiated with the same type sa the class
// postfix: increment/decrement the object but return the unchanged value
template<typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    // no check needed here; the call to prefix increment will do the check
    BlobPtr ret = *this;    // save the current value
    ++*this;    // advance one element; prefix++ checks the increment
    return ret; // return the saved state
}

// Class Templates and friends

// One-to-one friendship
// forward declarations needed for friend declarations in Blob
// see 161.h

// General and Specific Template Friendship
// a class can also make every instantiation of another template its friend, or it may limit friendship to a specific
// instantiation:
// forward declaration necessary to befriend a specific instantiation of a template
template<typename T>
class Pal;

class C {
    friend class Pal<C>;    // Pal instantiated with class C is a friend to C
    // all instances of Pal2 are friend to C;
    // no forward declaration required when we befriend all instantiations
    template<typename T> friend
    class Pal2;

};

template<typename T>
class C2 {
    // each instantiation of C2 has the same instance of Pal as friend
    friend class Pal<T>;    // a template declaration for Pal must be in scope
    // all instances of Pal2 are friends of each instance of C2, prior declaration needed
    template<typename X> friend
    class Pal2;

    // Pal3 is a nontemplate class that is a friend of every instance of C2
    friend class Pal3;  // prior declaration for Pal3 not needed
};

// Befriending the template's own type parameter
// under the new stand, we can make a template type parameter a friend
template<typename Type>
class Bar {
    friend Type;    // grants access to the type used to instantiate Bar
};

// Template Type Aliases


int main() {
    // example 1
    cout << compare(1, 0) << endl;   // T is int
    vector<int> vec1{1, 2, 3}, vec2{4, 5, 6};
    cout << compare(vec1, vec2) << endl; // T is vector<int>

    // example 2
    compare2("hi", "mom");
    // will use the size of the literals to instantiate. Which will instantiate int compare(const char (&p1)[3], const char (&p2)[4])

    // example 3: Instantiate a class template
    Blob<int> ia;   // empty Blob<int>
    Blob<int> ia2 = {0, 1, 2, 3, 4};    // Blob<int> with five elements
    // the compiler generates a different class for each element type we specify:
    Blob<string> names;
    Blob<double> prices;

    // example 4
    Blob<string> articles = {"a", "b", "c"};

    // example 5
    // Instantiate Blob<int> and the initializer_list<int> constructor
    Blob<int> squares = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // Instantiate Blob<int>::size() const
    for (size_t i = 0; i != squares.size(); ++i)
        squares[i] = i * i;    // Instantiate Blob<int>::operator[](size_type)


}


