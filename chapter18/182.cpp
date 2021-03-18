//
// Created by fiberhome on 2021/3/15.
//
#include "string"
#include "iostream"
#include "../chapter13/Sales_data.h"

using namespace std;
// Namespaces

// 182.1 namespace definitions
namespace cplusplus_primer {
    class Sales_data {/* ...*/};

    Sales_data operator+(const Sales_data &, const Sales_data &);

    class Query {
    };

    class Query_base {
    };
}
// above defines a namespace named cplusplus_primer with four members

// namespace can be discontiguous
namespace nsp {
    // declarations
}
// either define a new namespace or adds to an existing one.
// best practice: namespaces that define multiple, unrelated types should use separate files to represent each type

// Defining the Primer Namespace
// Using above strategy for separating interface and implementation, The declaration for Sales_data and its functions
// would be placed in Sales_data.h, those for Query would be in Query.h. And corresponding implementation files in files
// such as Sales_data.cc, Query.cc.

// / ---- Sales_data.h----
//// #includes should appear before opening the namespace
//#include <string>
//namespace cplusplus_primer {
//class Sales_data { /* ... */};
//Sales_data operator+(const Sales_data&,
//const Sales_data&);
//// declarations for the remaining functions in the Sales_data interface
//}
//// ---- Sales_data.cc----
//// be sure any #includes appear before opening the namespace
//#include "Sales_data.h"
//namespace cplusplus_primer {
//// definitions for Sales_data members and overloaded operators
//}

// Defining Namespace members
// #include "Sales_data.h"
//namespace cplusplus_primer { // reopen cplusplus_primer
//// members defined inside the namespace may use unqualified names
//std::istream&
//operator>>(std::istream& in, Sales_data& s) { /* ... */}
//}

// Template specializations
// declare in the namespace, we can define outside the namespace
namespace std {
    template<>
    struct hash<Sales_data>;
}
template<>
struct std::hash<Sales_data> {
};

// The Global namespace
// ::member_name

// Nested namespaces
namespace cplusplus_primer {
    // first nested namespace: defines the Query portion of the library
    namespace QueryLib {
        class Query {
        };

        Query operator&(const Query &, const Query);
    }

    // second nested namespace: ... Sales_data ...
    namespace Bookstore {
        class Quote {
        };

        class Disc_quote : public Quote {
        };
    }
}

// Inline namespaces
inline namespace FifthEd {

}
namespace FifthEd {  // implicitly inline
    class Query_base {
    };

}
// Inline namespaces are often used when code changes from one release of an application to the next.
// for example, put code from the current ed into an inline namespace
namespace FourthED {
    class Item_base {
    };

    class Query_base {
    };
}
// assuming that each namespace was defined in a header, define as follow:
namespace cplusplus_primer {

#include "FifthEd.h"
#include "FourthEd.h"

}

// because fifth is inline, cplusplus_primer:: will get the version from that namespace. If we want the earlier edition,
// should used cplusplus_primer::FourthEd::xxx.

// Unnamed namespaces
// variables in an unnamed namespace have static lifetime: created before their first use and destroyed when the program ends
// Note: unnamed namespace is local to a particular file and never spans multiple files
int i;  // global declaration for i
namespace {
    int i;
}

// ambiguous: defined globally and in an unnested, unnamed namespace,
// see main
// If the unnamed namespace is nested, then names in it are accessed in a normal way, using the enclosing name
namespace local {
    namespace {
        int i;
    }
}

// 182.2 Using namespace members
// namespace alias
namespace cplusplus_primer {};
namespace primer = cplusplus_primer;
// also useful for a nested namespace
namespace Qlib = cplusplus_primer::QueryLib;
Qlib::Query qq;

// using declarations: a recap

// using directives
// begins with the keyword using, followed by the keyword namespace

// using directives and scope
// In the case of using declaration, we are simply making name directly accessible in the local scope
// In contrast, a using directives makes the entire contents of a namespace available
// simplest case: a namespace A and a func f, both defined at global scope.
// If f has a using directive for A, then in f it will be as if the names in A appeared in the global scope prior to
// to the definition of f
namespace A {
    int ii, j;
}

void f() {
    using namespace A;  // injects the names from A into the global scope
    cout << ii * j << endl;  // use i and j from namespace A
}

// using directive example
namespace blip {
    int i = 16, j = 15, k = 23;
    // other
}
int j = 0;    // ok: j inside blip is hidden inside a namespace
void manip() {
    // using directive; the names in blip are "added" to the global scope
    using namespace blip;   // clash between ::j and blip::j
    // detected only if j i used
    ++i;    // sets blip::i to 17
    ++j;    // error ambiguous: global j or blip::j?
    ++::j;  // ok: sets global j to 1
    ++blip::j;  // ok: blip::j to 1
    int k = 97; // local k hides blip::k
    ++k;    // sets local k to 98
}

// Headers and using declaration or directives
// caution: avoid using directives

// 182.3 classes, namespaces, and scope
namespace A {
    int i;
    namespace B {
        int i;  // hides A::i within B
        int j;

        int f1() {
            int j;  // j is local to f1 and hides A::B::j
            return i;   // returns B::i
        }
    }   // namespace B is closed and names in it are no longer visible
    int f2() {
        return j;   // error: j is not defined
    }

    int j = i;  // initialized from A::i
}
// when a class is wrapped in a namespace, the normal lookup still happens:
namespace A {
    int i;
    int k;

    class C1 {
    public:
        C1() : i(0), j(0) {}    // ok: initializes C1::i and C1::j
        int f1() { return k; } // returns A::k
        int f2() { return h; } // error: h is not defined
        int f3();

    private:
        int i;  // hides A::i within C1
        int j;
    };

    int h = i;  // initialized from A::i
}

// member f3 is defined outside class C1 and outside namespace A
int A::C1::f3() { return h; }   // ok: returns A::h
// since f3 is defined after A::h, it can use h.

// Argument-Dependent lookup and parameters of class type
// consider the following simple program:
// see example 3

// Lookup and std::move and std::forward
// suggest always using the fully qualified versions of these names. std::move instead of move

// Friend declarations and argument-dependent lookup
namespace A {
    class C {
        // two friends: neither is declared apart from a friend declaration
        // these functions implicitly are members of namespace A
        friend void f2();   // won't be found, unless otherwise declared
        friend void f(const C &);    // found by argument-dependent lookup
    };
}
// see example 4

// 182.4 Overloading and Namespaces
// argument-dependent lookup and overloading
namespace NS {
    class Quote {
    };

    void display(const Quote &) {}
}
class Bulk_item : public NS::Quote {
};
// see example 5

// Overloading and using declarations
using NS::print(int); // error: cannot specify a parameter list
using NS::print; // ok: using declarations specify names only

// Overloading and using directives
namespace libs_R_us {
    extern void print(int);

    extern void print(double);
}

void print(const std::string &);
// using directives adds names to candidate set for calls to print:
using namespace libs_R_us;

void fooBar(int ival) {
    print("val: ");     // calls global print(const string&)
    print(ival);    // calls libs_R_us::print(int)
}

// Overloading across multiple using directives
namespace AW {
    int print(int);
}
namespace Primer {
    double print(double);
}
// using directives create an overload set of functions from different namespaces
using namespace AW;
using namespace Primer;

long double print(long double);
// see example 6

int main() {
    // 182.1 Namespace definitions
    // see above

    // Each namespace is a scope
    cplusplus_primer::Query q = cplusplus_primer::Query();

    // namespace can be discontiguous

    // ambiguous: defined globally and in an unnested, unnamed namespace,

    i = 10;

    local::i = 42;

    // example 3
    std::string s;
    std::cin >> s;
    // this is equivalent to
    operator>>(std::cin, s);

    // example 4
    A::C cobj;
    f(cobj);    // ok: finds A::f through the friend declaration in A::C
    f2();   // error: A::f2 not declared
    // Because f takes an argument of a class type, and f is implicitly declared in the same namespace as C, f is found
    // Because f2 has no parameter, it will not be found

    // example 5
    Bulk_item book1;
    display(book1);

    // example 6
    print(1); // calls AW::print(int)
    print(3.1); // calls Primer::print(double)


}