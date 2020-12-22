//
// Created by fiberhome on 2020/11/23.
//
#include <iostream>
#include "string"
#include "cctype"
#include "vector"

using namespace std;

int main() {
    // if else braces. If not using brace, a dangling else will happen,
    // which cause the outer else match the inner if.
//    int grade = 5;
//    string lettergrade;
//    if (grade % 10 >= 3)
//        if (grade % 10 > 7)
//            lettergrade += "+";
//    else
//        lettergrade += "-";
//
//    cout << lettergrade << endl;

    // switch
//    char ch = 'e';
//    int vowelCnt;
//    int otherCnt;
//    switch (ch) {
//        case 'a':
//        case 'e':
//        case 'i':
//        case 'o':
//        case 'u':
//            ++vowelCnt;
//            break;
//        default:
//            ++otherCnt;
//            break;
//    }

//    string buf;
//    cin>>buf;
//    bool flag =buf.empty();
//    cout<<flag<<endl;
//    while (cin >> buf && !buf.empty()) {
//        switch (buf[0]) {
//            case '-':
//                for (auto it = buf.begin() + 1; it != buf.end(); ++it) {
//                    if (*it == ' ')
//                        break;
//                    else cout<<*it<<endl;
//                }
//                break;
//            case '+':
//                break;
//        }
//    }

    //goto statement
    begin:
        int sz=-1;
        cout<<sz<<endl;
        if (sz<=0){
            goto begin;
        }
    return 0;
}
