//
// Created by fiberhome on 2020/12/24.
//

#include "76_static_class_member.h"

int main() {
    double r;

    // similar as the staticmethod decorator in python.
    r = Account::rate(); // access a static member using the scope operator.

    // even though static members are not part of the objects of its class,
    // we can use an object, reference, or pointer of class type to access
    Account ac1;
    Account *ac2 = &ac1;
    r = ac1.rate();
    r = ac2->rate();
}
