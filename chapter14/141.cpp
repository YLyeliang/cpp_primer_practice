//
// Created by yel on 2021/2/19.
//
// Chpater 14: Overloaded Operations and Conversions

#include "iostream"

using namespace std;

// 141: basic concept
// Overloaded operators: the keyword operator followed by the symbol for the operator being defined
// xxx has a return type, parameter list, and a body

int main() {
    // an operator function must either be a member of a class or have at least one parameter of class type
    int operator+(int, int); // error: built-in type

    // most operator can be overloaded, except :: .* . ?:

    // calling an overloaded operator function directly
    // equivalent calls ot nonmember operator function

    data1 + data2;    //nor mal expression
    operator+(data1, data2); // equivalent function call

    data1 += data2; // expression-based "call"
    data1.operator+=(data2);    // equivalent call to member operator function

    // some operators shouldn't be overloaded
    // && || comma address-of

    // use definitions that are consistent with the built-in meaning
    // if the class does IO. define the shift operator to be consistent with how IO is done for the built-in type
    // If the class has an operation to test for equality, define operator==, operator!=
    //

    // assignment and compound assignment

    // choosing member or nonmember implementation
    // The assignment(=), subscript([]), call(()), and member access arrow(->) must be defined as members
    // Symmetric operators- those that might convert the either operand, such as the arithmetic, equality, relational,
    // and bitwise operators- usually should be defined as ordinarily nonmember functions.

    // when define an operator as a member function, then the left-hand operand must be an object of the class of
    // which that operator is a member.
    string s = "world";
    string t = s + "!";   // ok: we can add a const char* to a string
    string u = "hi" + s;    // would be an error if + were a member of string


}




