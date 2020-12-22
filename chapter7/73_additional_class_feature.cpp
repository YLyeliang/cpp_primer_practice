//
// Created by fiberhome on 2020/12/15.
//
#include "73_head.h"


int main() {
    Screen myscreen;
    char ch = myscreen.get();
    ch = myscreen.get(0, 0); // overloaded functions.
    myscreen.move(4, 0).set('#'); // move and set value
    // If didn't define &Screen, this would create a tmp Screen variable, not change myscreen.

    // can use class class_name xx to define a class type.
    // each class have a unique type.
//    Screen screen1;
//    class Screen screen2;

}


