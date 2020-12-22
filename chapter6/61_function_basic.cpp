//
// Created by fiberhome on 2020/11/27.
//

#include "chapter6.h"
#include "string"
#include "iostream"

using namespace std;

bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

// if the first argument is defined as string , not const string.
// the call in main is an error.
string::size_type find_char(const string &s, char c, string::size_type &occurs) {
    auto ret = s.size();
    occurs = 0;
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}

//Ellipsis Parameters
void foo(const string &s,...);


// we can use initializer_list to represent an array of values of the specified type.
void error_msg(initializer_list<string> ls){
    for (const auto & l : ls)
        cout<<l<<endl;
}
// argv[0] contains the program's name. Optional arguments begin in argv[1]

int main(int argc,char **argv) {


    string a1 = "ac";
    string a2 = "acd";

    bool flag = isShorter(a1, a2);
    cout << flag << endl;

    string::size_type ctr;
    auto index = find_char("Hello_word", 'o', ctr);

    // array: when pass an array to function, actulally we passing a pointer
    // to the array's first element.

    // these are equivalent, each func has a single parameter of type
    // const int *
    void print(const int *);
    void print(const int[]);
    void print(const int[10]);

    int j[]={1,2};

}
