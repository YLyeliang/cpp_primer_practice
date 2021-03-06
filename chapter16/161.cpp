//
// Created by yel on 2021/2/28.
//
#include<vector>
#include "string"
#include "iostream"
#include "memory"
#include "list"

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
// we can define typedef that refers to a instantiated class
typedef Blob<string> StrBlob;
// However, since template is not a type, we can't define typedef Blob<T>
// Instead, we use using keyword
template<typename T> using twin = pair<T, T>;
twin<string> author;
// When we define a template type alias, we can fix one or more of the template parameters
template<typename T> using partNo = pair<T, unsigned>;
partNo<string> books;   // book is a pair<string,unsigned>

// static members of class template
template<typename T>
class Foo {
public:
    static size_t count() { return ctr; }

private:
    static size_t ctr;
};

// instantiates static members Foo<string>::ctr and Foo<string>::count
Foo<string> fs;
// all three objects share the same Foo<int>::ctr and Foo<int>::count members
Foo<int> fi, fi2, fi3;
template<typename T>
size_t Foo<T>::ctr = 0;   // define and initialize ctr
// example 6

// 161.3 Template parameters
// a template parameter name has no intrinsic meaning, normally it's T, but we can use any other name.

// Template parameters and scope
// The name of a template parameter name can be used after it has been declared and until the end of the template declaration
// or definition.
typedef double A;

template<typename A, typename B>
void f(A a, B b) {
    A tmp = a;    // tmp has same type as template parameter A, not double
    double B;   // error: redeclares template parameter B
}

// Because a parameter name cannot be reused, the name of a template parameter can appear only once
// error: illegal reuse of template parameter name V
template<typename V, typename V>
void ff() {}
// ...

// Template Declarations
// a template declaration must include the template parameters
// declares but doesn't define compare and Blob
template<typename T>
int compare(const T &, const T &);

template<typename T>
class Blob;

// all three uses of calc refers to the same function template
template<typename T>
T calc(const T &, const T &);   // declaration
template<typename U>
U calc(const U &, const U &);   // declaration
// definition of the template
template<typename Type>
Type calc(const Type &a, Type &b) {/**/}

// Using class members that are types
// Assuming T is a name of a type parameter, when the compiler see a statement of the following form:
// T::size_type * p
// it needs to know whether we're defining a variable named p or are multiplying a static data member named size_type by
// a variable named p
// we must explicitly tell the compiler a type member of a template type is a type. By using typename
template<typename T>
typename T::value_type top(const T &c) {
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}
// top expects a container as its argument and use a typename to specify its return type and to generate a value initialized
// element to return if c has no elements

// Default Template Arguments
// rewrite compare to use the library less function-object template by default:
// compare has a default template argument, less<T>
// and a default function argument, F()
template<typename T, typename F=less<T>>
int compare2(const T &v1, const T &v2, F f = F()) {
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}
// when users call this version of compare, they may supply their own comparison operation but are not required to do so.
// see example 7

// template default arguments and class templates
template<class T =int>
class Numbers {  // by default T is int
public:
    Numbers(T v = 0) : val(v) {}

private:
    T val;

};
// instantiation see example 8

// 161.4 Member Templates
// A class, may have a member function that is itself a template, such members are referred to as member templates,
// and may not be virtual
// function-object class that calls delete on a given pointer
class DebugDelete {
public:
    DebugDelete(ostream &s = cerr) : os(s) {}

    // as with any function template, the type of T is deduced by the compiler
    template<typename T>
    void operator()(T *p) const {
        os << " deleting unique_ptr" << endl;
        delete p;
    }

private:
    ostream &os;
};
// see example 9

// Member template of class template
// we'll give our Blob class a constructor that will take two iterators denoting a range of elements to copy.
// since we'd like to support iterators into varying kinds of sequences, we'll make this constructor a template
template<typename T>
class Blob2 {
public:
    template<typename It>
    Blob2(It b, It e);

private:
    shared_ptr<vector<T>> data;
};

// When we define a member template outside the body of a class template, we must provide the template parameter list
// for the class template and for the function template
// type parameter for the class
template<typename T>
// type parameter for the constructor
template<typename It>
Blob2<T>::Blob2(It b, It e) :data(make_shared<vector<T>>(b, e)) {}

// Instantiation and Member Templates
// see example 10

// 161.5 Controlling Instantiations
// When two or more separately compiled source files use the same template with the same template arguments, there is an
// instantiation of that template in each of those files.
// In large system, the overhead of instantiating the same template in multiple files can become significant.
// we can avoid this overhead through an explicit instantiation:
// extern template declaration;    // instantiation declaration
// template declaration;   // instantiation definition
extern template
class Blob<string>;   // declaration
template int compare(const int &, const int &);   // definition
// when the compiler sees an extern template declaration, it will note generate code for that instantiation in that file,
// declaring an instantiation as extern is a promise that there will be a non-extern use of that instantiation elsewhere.

// instantiation file must provide a (non-extern) definition for every
// type and function that other files declare as extern
template
class Blob<string>;    // instantiates all members of the class template
// see example in 1615.cpp, the compare<int> and Blob<string> will not be instantiated in that file
// the definitions for compare instantiated with int and Blob<string> will contained in this file.
// when we build the application, we must link both files.

// Instantiation definitions instantiates all members
// an instantiation definition can be used only for types that can be used with every member function of a class template.

// 161.6 Efficiency and flexibility
// The library smart pointer types offer a good illustration of design choices faced by designers of templates
// The difference between shared_ptr and unique_ptr is the strategy they use in managing the pointer they hold
// we can easily override the deleter of a shared_ptr by passing a callable object when we create or reset the pointer.
// In contrast, the type of the deleter is part of the type of a unique_ptr object

// Binding the Deleter at runtime
// we can infer that shared_ptr must access its deleter indirectly

// Binding the deleter at compiler time
// in the unique_ptr, the type of the deleter is part of the type of the unique_ptr


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

    // example 6
    Foo<int> f1;    // instantiate Foo<int> class and the static data member ctr
    auto ct = Foo<int>::count();    // instantiate Foo<int>::count
    ct = f1.count();    // uses Foo<int>::count
    ct = Foo::count();   // error: which template instantiation?

    // example 7
    bool i = compare2(0, 42);    // use less; i is -1
    // result depends on the isbns in item1 and item2
    Sales_data item1(cin), item2(cin);
    bool j = compare2(item1, item2, compareIsbn);

    // example 8
    Numbers<long double> lots_of_precision;
    Numbers<> average_precision;    // empty <> says we want the default type

    // example 9
    double *p = new double;
    DebugDelete d;  // an object act like a delete expression
    d(p);   // calls DebugDelete::operator()(double *), which delete p
    int *ip = new int;
    // calls operator()(int*) on a temporary DebugDelete object
    DebugDelete()(ip);
    // we can use DebugDelete as the deleter of a unique_ptr. To override the deleter of a unique_ptr, we supply the
    // type of the deleter inside the brackets and supply an object of the deleter type to the constructor.
    // destroying the object to which p points
    // instantiates DebugDelete::operator()<int>(int*)
    unique_ptr<int, DebugDelete> p(new int, DebugDelete());
    // destroying the object to which sp points
    // instantiates DebugDelete::operator()<string>(string*)
    unique_ptr<string, DebugDelete> sp(new string, DebugDelete());

    // example 10
    int ia3[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<long> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<const char *> w = {"now", "is", "the", "time"};
    // instantiate the Blob<int> class
    // and the Blob<int> constructor that has two int* parameters
    Blob2<int> a1(begin(ia3), end(ia3));
    // instantiate the Blob<int> constructor that has two vector<long>::iterator parameters
    Blob2<int> a2(vi.begin(), vi.end());
    // instantiate the Blob<string> class and the Blob<string> constructor that has two list<const char*>::iterator parameters
    Blob2<string> a3(w.begin(), w.end());


}


