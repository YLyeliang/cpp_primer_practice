//
// Created by fiberhome on 2021/3/15.
//
#include "iostream"
#include "exception"
#include "../chapter13/Sales_data.h"

using namespace std;
// 18 Tools for large programs
// 18.1 Exception Handling

int main() {
    // 181.1 Throwing an exception
    // statements following a throw are not executed.

    // Stack Unwinding
    // try catch searching process.
    // an exception that is not caught terminates the program.

    // Objects are automatically destroyed during stack unwinding

    // Destructors and Exceptions
    // During stack unwinding, destructors are run on local objets of class type.
    // Because destructors are run automatically, they should not throw. If, during stack unwinding, a destructor
    // throws an exception that it does not also catch, the program will be terminated.

    // The Exception Object
    // Throwing a pointer requires that the objects to which the pointer points exist whenever the corresponding
    // handler resides

    // 181.2 Catching an exception
    // Ordinarily, a catch that takes an exception of a type related by inheritance ought to define its parameters
    // as a reference.

    // Finding a Matching Handler
    // the selected catch is the first one that matches the exception at all.

    // Rethrow
    catch (my_error & eObj)
    {    // specifier is a reference type
        eObj.status = errCodes::severeErr;  // modifies the exception object
        throw;  // the status member of the exception object is severeErr
    } catch(other_error
    eObj){ // specifier is a nonreference type
        eObj.status = errCodes::badErr; // modifies the local copy only
        throw;  // the status member of the exception object is unchanged
    }

    // The Catch-All handler
    // cat(...), match any type of exception
    void manip() {
        try {
            // operations cause an exception to thorw
        }
        cath(...)
        {
            // some work
            throw;
        }
    }
    // Note: catch(...) is used in combination with other catch clauses, it must be last.

    // 181.3 Function try Blocks and Constructors
    try {
        //
    } catch (exception) {
        // ...
    } catch (const runtime_error &re) {
        // ...
    } catch (overflow_error eObj) {}

    // To handle an exception from a constructor initializer, we must write the constructor as a function try block
    // wrap the Blob in 161.2, see 181.h

    // 181.4 The noexcept Exception Specification
    // provide a noexcept to specify that a function doesn't throw exceptions
    void recoup(int) noexcept;  // won't throw      nonthrowing specification
    void alloc(int);    // might throw
    // noexcept must appears on all of the declarations and the corresponding definition

    // Violating the Exception Specification
    // this function will compile, even though it clearly violate its exception specification
    void f() noexcept   // promises not to throw any exception
    {
        throw exception();  // violates the exception specification
    }
    // If noexcept does throw, terminate is called
    // noexcept should be used in two cases: 1. we are confident; 2. we don't know what to do to handle the error

    // Arguments to the noexcept Specification
    // noexcept takes an optional argument that must be convertible to bool
    void recoup2(int) noexcept(true);   // won't throw
    void alloc2(int) noexcept(false);   // can throw

    // The noexcept operator
    // for example, this expression yield true:
    noexcept(recoup2(i));   // true if calling recoup can't throw, false otherwise
    // More generally,
    // noexcept(e)
    // is true if functions called by e have nonthrowing specifications and e itself doesn't contain a throw
    void f() noexcept(noexcept(g()));   // f has same exception specifier as g

    // Exception Specification and pointers, virtuals, and copy control
    // both recoup and pf1 promise not to throw
    void (*pf1)(int) noexcept =recoup2;
    // ok: recoup won't throw; it doesn't matter that pf2 might
    void (*pf2)(int) =recoup2;

    pf1 = alloc2;    // error: alloc might throw but pf1 said it wouldn't
    pf2 = alloc2;   // ok: both might throw

    // If a virtual function includes a promise not to throw, the inherited virtuals must also promise not to throw
    class Base {
    public:
        virtual double f1(double) noexcept; // doesn't throw
        virtual int f2() noexcept(false);   // can throw
        virtual void f3();
    };
    class Derived : public Base {
    public:
        double f1(double);  // error: Base::f1 promises not to throw
        int f2() noexcept(false);    // ok: same specification as Base::f2
        void f3() noexcept; // ok: Derived f3 is more restrictive
    };

    // 181.5 Exception class Hierarchies
    // Exception classes for a bookstore application
    class out_of_stock : public runtime_error {
    public:
        explicit out_of_stock(const string &s) : runtime_error(s) {}
    };
    class isbn_mismatch : public logic_error {
    public:
        explicit isbn_mismatch(const string &s) : logic_error(s) {}

        isbn_mismatch(const string &s, const string &lhs, const string &rhs) : logic_error(s), left(lhs), right(rhs) {}

        const string left, right;
    };

    // using our own exception types
    // throws an exception if both objects do not refer to the same book
    Sales_data &
    Sales_data::operator=(const Sales_data &rhs) {
        if (isbn() != rhs.isbn())
            throw isbn_mismatch("wrong isbn", isbn(), rhs.isbn());
        units_sold = rhs.units_sold;
        return *this;
    }




}
