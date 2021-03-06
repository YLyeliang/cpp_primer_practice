//
// Created by yel on 2021/2/19.
//

#include <map>
#include <functional>
#include "string"
#include "iostream"
#include "../Sales_data.h"
#include "vector"
#include "../chapter12/StrBlobPtr.h"
#include "algorithm"

using namespace std;

// Input and Output Operators

// overloading the output operator <<
ostream &operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

// overloading the input operator >>
istream &operator>>(istream &is, Sales_data &item) {
    double price;   // no need to initializes; we'll read into price before we use it
    is >> item.bookNo >> item.units_sold >> price;
    if (is) // check that the inputs succeeded
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();    // input failed; give the object the default state
    return is;
}

// assumes that both objects refers to the same book
Sales_data
operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;   // copy data members from lhs into sum
    sum += rhs; // add rhs into sum
    return sum;
}

// Equality operators
bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() == rhs.isbn() &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
    return !(lhs == rhs);
}
// The definition of equality are trivial.

// Relational operators
// Ordinarily the relational operators should
// 1. Define an ordering relation that is consistent with the requirements for use as a key to an associative container;
// 2. Define a relation that is consistent with == if the class has both operators.

// compound assignment operators
Sales_data &Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// 148 Function-call absInt
struct absInt {
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};

class PrintString {
public:
    explicit PrintString(ostream &o = cout, char c = ' ') :
            os(o), sep(c) {}

    void operator()(const string &s) const { os << s << sep; }

private:
    ostream &os;    // stream on which to write
    char sep;   // character to print after each output
};

class ShorterString {
public:
    bool operator()(const string &a1, const string &a2) const { return a1.size() < a2.size(); }
};

int add(int i, int j) { return i + j; }

Sales_data add(const Sales_data &, const Sales_data &);

class SmallInt {
public:
    SmallInt(int i = 0) : val(i) {
        if (i < 0 || i > 255)
            throw out_of_range("Bad SmallInt value");
    }

    explicit operator int() const { return val; }

private:
    size_t val;
};

int main() {
    // overloading the output operator <<

    // IO operators must be nonmember functions
    Sales_data data;
    data << cout;   // if operator<< is a member of Sales_data
    // usually, IO operators must be declared as friends

    // overloading the input operator >>


    // 143 Arithmetic and Relational Operators
    // Ordinarily, we define the arithmetic and relational operators as nonmember functions

    // Equality operators

    // Relational operators

    // 144 Assignment Operators
    // In addition to the copy- and move-assignment that assign the same type.
    // a class can define additional assignment operators that allow other types as the right-hand operand

    // for example, the vector
    vector<string> v;
    v = {"a", "b"};
    // we can add this operator to our StrVec as well.
    // see 135.h

    // compound assignment operators
    // which are not required to be members. However, we prefer to define all assignments, including compound assignment,
    // in the class.

    // 145 Subscript Operator
    // The subscript operator must be a member function
    // If a class has a subscript operator, it usually should define two versions: one that returns a plain reference,
    // other that is a const member and returns a reference to const
    // As a example, see StrVec in 135.h

    // 146 Increment and Decrement Operators
    // these operators change the state of the object on which they operate, our preference is to make them members.
    // define increment or decrement operators should define both the prefix and postfix versions
    // see StrBlobPtr class in chapter12/StrBlobptr.h

    // Calling the Postfix Operators Explicitly
    StrBlobPtr a1 = {"a", "b", "c"};
    StrBlobPtr p(a1);   // p points to the vector inside a1
    p.operator++(0);    // call postfix operator++
    p.operator++();     // call prefix operator++

    // 147 Member Access Operators
    // The dereference(*) and arrow(->) operators are often used in classes that represent iterators and
    // in smart pointer classes.
    // see StrBlobPtr.h

    *p = "okay";
    cout << p->size() << endl;  // print 4, the size of the first element in a1
    cout << (*p)->size() << endl;

    // Constraints on the Return from Operator Arrow

    // 148 Function-Call Operator
    // absInt
    int i = -42;
    absInt absObj;  // object that has a function-call operator
    int ui = absObj(i); // passes i to absObj.operator()
    // note: the funciton-call operator must be a member function
    // A class may define multiple versions of the call operator, each of which must differ as to the number or types
    // of their parameters

    // Function-Object Classes with State
    // see PrintString class above
    string s = "hehe";
    PrintString printer;    // uses the default; prints to cout
    printer(s); // print s followed by a space on cout
    PrintString errors(cerr, '\n');
    errors(s);  // print s followed by a newline on cerr
    // Function objects are most often used as arguments to the generic algorithms
    vector<string> vs = {"a", "b", "c"};
    for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));

    // 148.1 Lambdas are function objects
    // rethink the lambda usage of stable_sort in 101.cpp
    // it acts like a unnamed object of a class that would look something like  above: ShorterString
    stable_sort(words.begin(), words.end(), ShorterString()); // replace the lambda as function-object class

    // classes representing lambdas with captures

    // 148.2 Library-Defined function objects
    // The standard library defines a set of classes that represent the arithmetic, relational, and logical operators
    plus<int> intAdd;   // function object that can add two int values
    negate<int> intNegate;  // function object that can negate two int values
    // use intAdd::operator(int,int) to add 10 and 20
    int sum = intAdd(10, 20);    // sum=30
    sum = intNegate(intAdd(10, 20)); // sum=-30
    // uses intNegate::operator(int) to generate -10 as the second parameter to intAdd::operator(int,int)
    sum = intAdd(10, intNegate(10));  // sum=0
    // these are defined in the functional header.

    // Using a library function object with the algorithms
    vector<string *> nameTable; // vector of pointers
    // error: the pointers in nameTable are unrelated, so < is undefined
    sort(nameTable.begin(), nameTable.end(), [](string *a, string *b) { return a < b; });
    // ok: library guarantees that less on pointer types is well defined
    sort(nameTable.begin(), nameTable.end(), less<string *>());

    // 148.3 Callable objects and function
    // different types can have the same call signature
    // ordinary function see above

    // lambda, which generates an unnamed function-object class
    auto mod = [](int i, int j) { return i % j; };
    // function-object class
    struct div {
        int operator()(int denominator, int divisor) {
            return denominator / divisor;
        }
    };
    // each of above share the same call signature: int (int, int)
    // maps an operator to an pointer to a function taking two ints and returning an int
    map<string, int (*)(int, int)> binops;
    // ok: add is a pointer to function of appropriate type
    binops.insert({"+", add});
    // However, we can't store mode or div in binops
    binops.insert({"%", mod});   // error: mod is not a pointer to function
    // because lambda has its own class type. That type doesn't match the type of the value in binops.

    // The library function type
    // we can solve above problem using a new library type named function that is defined in functional header
    // function<T> f;    f is a null function object that can store callable objects with a call signature that
    // is equivalent to the function type T
    // function<T> f(nullptr)
    // function<T> f(obj)
    // f(args)  use
    // Types defined as members of function<T>
    // result_type  The type returned by this function type's callable object
    // argument_type
    // first_argument_type
    // second_argument_type
    function<int(int, int)> f1 = add;   // declared a function type that can represent callable objects that return
    // an int result and have two int parameters
    function<int(int, int)> f2 = div(); // object of a function-object class
    function<int(int, int)> f3 = [](int i, int j) { return i * j; }; // lambda
    cout << f1(4, 2) << endl;   // print 6
    cout << f2(4, 2) << endl;    // print 2
    cout << f3(4, 2) << endl;    // print 8
    // now redefine the map
    map<string, function<int(int, int)>> binops2 = {
            {"+", add},
            {"-", minus<int>()},
            {"/", div()},
            {"*", [](int i, int j) { return i * j; }},
            {"%", mod}
    };

    binops2["+"](10, 5);     // calls add(10,5)
    binops2["-"](10, 5);     // uses the call operator of the minus<int> object
    binops2["/"](10, 5);     // uses the call operator of the div object
    binops2["*"](10, 5);     // calls the lambda function object
    binops2["%"](10, 5);     // calls the lambda function object

    // Overloaded Functions and function
    // we cannot store the name of an overloaded function in an object of type function:
    // see Sales_data add above

    map<string, function<int(int, int)>> binops3;
    binops3.insert({"+", add});  // error: which add?
    // one way to resolve the ambiguity is to store a function pointer instead of the name of the function
    int (*fp)(int, int) =add;   // pointer to the version that takes two ints
    binops3.insert({"+", fp});  // oK: fp points to the right version of add
    // Alternatively, we can use a lambda to disambiguate
    // ok: use a lambda to disambiguate which version of add we want to use
    binops3.insert({"+", [](int i, int j) { return i + j; }});

    // 149: Overloading, Conversions and Operators
    // A conversion operator converts a value of a class type to a value of some other type
    // operator type() const; type represents a type
    // As a example, define a small class see above smallInt
    SmallInt si;
    si = 4;   // implicitly converts 4 to SmallInt then calls SmallInt::operator=
    si + 3;   // implicitly converts si to int followed by integer addition

    // the double argument is converted to int using the built-in conversion
    SmallInt sii = 3.14;    // Calls the SmallInt(int) constructor
    // the SmallInt conversion operator converts sii to int
    sii + 3.14;   // that int it converted to double using the built-int conversion

    // conversion operators may not be defined to take parameters. No way to pass arguments.
//    class SmallInt;
//    operator int(SmallInt & );    // error: nonmember
//    class SmallInt {
//    public:
//
//        int operator int() const;   // error: cannot have a return type
//        operator int(int = 0) const; // error: cannot have parameter list
//        operator int *() const { return 42; }  // error: 42 is not a pointer
//    };

    // Conversion Operators can yield surprising results

    // explicit Conversion Operators
    // see class above the main()
    // As with explicit constructor, the compiler won't use an explicit conversion operator for implicit conversions
    SmallInt siii = 3;    // ok: the SmallInt constructor is not explicit
    siii + 3; // error: implicit is conversion required, but operator int is explicit
    static_cast<int>(siii) + 3;   // ok: explicitly request the conversion

    // Conversion to bool
    // when using a stream object in a condition, we use the operator bool that is defined for the IO types.
    // For example:
    int value;
    while (cin >> value);
    // above reads into value and returns cin, cin is implicitly converted by the istream operator bool conversion function

    // 149.2 Avoiding Ambiguous Conversions

    // Argument Matching and Mutual Conversions
    // In the following example, we've defined two ways to obtain an A from a B: either by using B's conversion operaotr
    // or by using the A constructor that takes a B:
    struct B;
    struct A {
        A() = default;

        A(const B &);    // converts B to A
        // other members
    };
    struct B {
        operator A() const; // also converts a B to an A
        // other members
    };
    A f(const A &);
    B b;
    A a = f(b);   // error ambiguous: f(B::operator A()) or f(A::(const B&))
    // we have to explicitly call the conversion operator or the constructor
    A aa1 = f(b.operator A());   // ok: use B's conversion operator
    A aa2 = f(A(b)); // ok: use A's constructor

    // Ambiguities and Multiple conversions to built-in types
    // ambiguities also occur when a class defines multiple conversions to ( or from) types that are themselves
    // related by conversions
    struct C {
        C(int = 0);  // usually a bad idea to have two
        C(double);  // conversions from arithmetic type
        operator int() const;   // usually a bad idea to have two
        operator double() const;    // conversion to arithmetic types
        // other members
    };
    void ff2(long double);
    C c;
    ff2(c); // error ambiguous: f(C::operator int()) or f(C::operator double())
    long lg;
    C c2(lg);   // error ambiguous: C::C(int) or C::C(double)

    // Overloaded Functions and Converting Constructors
    // ambiguities are easy to generate if a class defines both conversion operators and overloaded operators
    // Helpful rules of thumb:
    // 1. Don't define mutually converting classes- if class Foo has a constructor that takes an object of class Bar,
    // do not give Bar a conversion operator to type Foo
    // 2. Avoid conversion to the built-in arithmetic types.
    struct D {
        D(int);
        // other
    };
    struct E {
        E(int);
        // other
    };
    void manip(const D &);
    void manip(const E &);
    manip(10);  // error ambiguous: manip(D(10)) or mapnip(E(10))
    // D and E both have constructors that take an int. Hence, the call is ambiguous.
    // to disambiguate:
    manip(D(10));

    // Overloaded Functions and User-defined conversion
    //
    struct F {
        F(double);
        // other
    };
    void manip2(const D &);
    void manip2(const F &);
    // error ambiguous: two different user-defined conversions could be used
    manip2(10);
    // D has a conversion from int, F has a conversion from double. Both manip2 are viable

    // 149.3 Function matching and overloaded operators
    // overloaded operators are overloaded functions
    class SmallInt {
        friend SmallInt operator+(const SmallInt &, const SmallInt &);

    public:
        SmallInt(int = 0);

        operator int() const { return val; }

    private:
        size_t val;
    };
    // below are ambiguous:
    SmallInt s1, s2;
    SmallInt s3 = s1 + s2;  // uses overloade operators+
    int i = s3 + 0;   // error: ambiguous
    // the second addition is ambiguous, because we can convert 0 to SmallInt and use the SmallInt operator+,
    // or convert the s3 to int and use the built-in addition operators on ints.



}
