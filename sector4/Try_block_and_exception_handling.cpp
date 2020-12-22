//
// Created by fiberhome on 2020/11/26.
//

#include <iostream>
#include "string"
#include "cctype"
#include "vector"
#include "../Sales_data.h"

using namespace std;

int main() {
    Sales_data data1;
    Sales_data data2;
    data1.bookNo = "abc";
    data2.bookNo = "abc";
    if (data1.bookNo != data2.bookNo)
        throw runtime_error("The number of book are different.");

    // try block
//    try {
//        statements
//    } catch (exception-declaration) {
//        handler-statements
//    }catch (exception-declaration) {
//        handler-statements
//    } // ...

    while (cin >> data1.bookNo >> data2.bookNo) {
        try {
            data1.bookNo + data2.bookNo;
        } catch (runtime_error err) {
            cout<<err.what()<<"\n Try again? Enter y or n"<<endl;
            char c;
            cin>>c;
            if (!cin||c=='n')
                break; //break
        }
    }
    // C++ exceptions.
    // 1. exception header defines the most general kind of exception classes named exception.
    // 2. stdexcept: general-purpose exception.
    // 3. new: bad_alloc exception.
    // 4. type_info: bad_cast


    return 0;

}