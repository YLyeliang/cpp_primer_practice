//
// Created by fiberhome on 2020/12/22.
//

#ifndef NOW_CODE_74_HEAD_H
#define NOW_CODE_74_HEAD_H
#include "string"
int height;

class Screen{
public:
    typedef std::string::size_type pos;
    void setHeight(pos);
    pos height=0;
    };
Screen::pos verify(Screen::pos);
void Screen::setHeight(pos var) {
    // var: refers to parameter
    // height: refers to the class member.
    // verify: refers to the global function.
    height=verify(var);
}

#endif //NOW_CODE_74_HEAD_H
