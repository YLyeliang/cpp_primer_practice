//
// Created by fiberhome on 2021/3/24.
//
#include "string"
#include "iostream"
#include "194.h"

using namespace std;

// Pointer to Class Member
// a pointer that can point to a non-static member of a class


int main() {
    const string Screen::*pdata;    // points to a member of class Screen that has type const string
    // when initialize (or assign to) a pointer to member
    pdata = &Screen::contents;
    // the more efficient way:
    auto pdata2 = &Screen::contents;

    // using a pointer to data member
    Screen myscreen, *pScreen = &myscreen;
    // .* dereference pdata to fetch the contents member from object myScreen
    auto s = myscreen.*pdata;
    // ->* dereference pdata to fetch contents from the object to which pScreen points
    s = pScreen->*pdata;

    // example 2
    // data() returns a pointer to the contents member of class Screen
    const string Screen::*pdata3 = Screen::data();
    // fetch the contents of the object named myScreen
    auto s2 = myscreen.*pdata3;

    // example 3
    auto pmf = &Screen::get_cursor;

    // overload, by declaring the type explicitly
    char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
    pmf2 = &Screen::get;
    // The parenthesis is essential
    // error: non-member function p cannot have a const qualifier
    char Screen::*p(Screen::pos, Screen::pos) const;
    // unlike ordinary function pointers, no automatic conversion between a member function and a pointer to that member
    pmf = &Screen::get; // must explicitly use the address-of operator
    pmf = Screen::get;  // error: no conversion to pointer from member functions

    // Using a pointer to member function
    // call the function to which pmf points on the object to which pScreen points
    char c1 = (pScreen->*pmf)();
    // passes the arguments 0,0 to the two-parameter version of get on the object of myScreen
    char c2 = (myscreen.*pmf2)(0, 0);

    // Using type aliases for member pointers
    // Action is a type that can point to a member function of Screen
    // that returns a char and takes two pos arguments
    using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
    Action get = &Screen::get;  // get point to the get member of Screen
    // action takes a reference to Screen and a pointer to member function of Screen
    Screen &action(Screen &, Action = &Screen::get);
    // action is a function taking two parameters, which are a reference to a Screen object and ...
    // equivalent call:
    action(myscreen);   // use default
    action(myscreen, get);   // uses the variable get that we previously defined
    action(myscreen, &Screen::get);  // passes the address explicitly

    // Pointer-to-member function tables




}