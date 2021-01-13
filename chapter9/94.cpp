//
// Created by fiberhome on 2021/1/12.
//
#include <deque>
#include <forward_list>
#include "vector"
#include "string"
#include "list"
#include "array"
#include "iostream"
#include "../chapter7/Sales_data.h"
#include "stack"

using namespace std;


int main() {
    // 94. How a vector Grows
    // usually, vector would allocate more memory than given numbers, to reduce reallocate time
    // in adds number.

    // members to manage capacity
    // shrink_to_fit() Request to reduce capacity() to equal size()
    // capacity() Number of elements c can have before reallocation is necessary
    // reserve(n) Allocate space for at least n elements.

    // a call to reserve changes the capacity of vector only if the requested space exceeds the
    // current space. If less than current, it does nothing.
    // As a result, call to reserve will never reduce the amount of space that container uses.
    // and the resize is the same.

    // capacity and size

    // 95 Additional string Operations
    const char *cp = "Hello World!!!"; // null-terminated array
    char noNull[] = {'H', 'i'}; // not null terminated
    string s1(cp); // copy up to null  s1=="Hello World!!!"
    string s2(noNull, 2); // copy 2 characters ; =="Hi"
    string s3(noNull); // undefined: noNull not null terminated
    string s4(cp + 6, 5); // copy 5 starting at cp[6]
    string s5(s1, 6, 5); // same as above
    string s6(s1, 6); // copy from s1[6] to end of s1
    string s7(s1, 6, 20); // num exceed the end, so copy to the end
    string s8(s1, 16); // throw an out_of_range exception

    // substr
    string s("hello world");
    string ss2 = s.substr(0, 5); //s2=hello
    string ss3 = s.substr(6); // from index 6 to end
    string ss4 = s.substr(6, 11); // world
    string ss5 = s.substr(12); // exception

    // other way to change string
    // supports the sequential container assignment, assign, insert, erase
    s.insert(s.size(), 5, '!'); // insert 5 ! at the end
    s.erase(s.size() - 5, 5); // erase last 5
    const char *cc = "Stately, plump Buck";
    s.assign(cc, 7); // s=="stately"
    s.insert(s.size(), cc + 7);

    // The append and replace functions
    string sss("C++ Primer"), sss2 = s;
    sss.insert(sss.size(), "4th Ed");
    sss2.append("4th Ed"); // equivalent to above

    sss.erase(11, 3);
    sss.insert(11, "5th");
    sss2.replace(11, 3, "5th"); // equivalent to above

    // string search
    string name("AnnaBelle"); //安娜贝尔，灵异娃娃
    auto pos1 = name.find("Anna"); // pos1=0, find the first occurrence of args in s
    string lowercase("annabelle");
    pos1 = lowercase.find("Anna"); // return npos, since not match,
    string numbers("0123456789"), names("r2d2");
    // return 1
    auto pos = names.find_first_of(numbers); // find the first occurrence of any characters from args in s

    string dept("03714p3");
    // return 5,
    auto pos_dept = dept.find_first_not_of(numbers); // find the first occurrence of any characters from args not in s

    // Specifying where to start the search
    string::size_type pos_ = 0;
    // each iteration finds the next number in name
    while ((pos_ = names.find_first_not_of(numbers, pos_)) != string::npos) {
        cout << "found number at index:" << pos_
             << " element is " << names[pos_] << endl;
        ++pos_;
    }

    // searching backward
    string river("Mississippi");
    auto first_pos = river.find("is"); // 1
    auto last_pos = river.rfind("is"); // 4, find the last occurrence of args in s
    // also, find_last_of, find_last_not_of

    // The compare function

    // numeric conversions
    int i = 42;
    string s_int = to_string(i);
    double d = stod(s_int); // converts the s to float
    // stoi, stol, stoul, stoll, stoull, stof, stod, stold
    string s2_ = "pi = 3.14";
    // convert the first substring in s that starts with a digit, d = 3.14
    d = stod(s2_.substr(s2_.find_first_of("+-.0123456789")));

    // container adapter
    // stack, queue, priority_queue
    // A container adapter takes an existing container type and makes it act like a different type.
    deque<int> deq={0,1,2,3};
    stack<int> stk(deq); // copies from deq into stk



}