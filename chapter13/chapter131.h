//
// Created by yel on 2021/2/3.
//

#ifndef NOW_CODE_CHAPTER131_H
#define NOW_CODE_CHAPTER131_H

class Foo {
public:
    Foo(); //default constructor

    // the first parameter must be a reference type.
    Foo(const Foo &);  // copy constructor

    Foo& operator=(const Foo&); // assignment operator
    // ...


};



#endif //NOW_CODE_CHAPTER131_H
