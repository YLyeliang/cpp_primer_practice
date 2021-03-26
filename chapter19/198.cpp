//
// Created by fiberhome on 2021/3/26.
//
#include "198.h"
#include "string"


int main() {
    volatile int v; // v is a volatile int
    int *volatile vip; // vip is a volatile pointer to int
    volatile int *ivp; // ivp is a pointer to volatile int
// vivp is a volatile pointer to volatile int
    volatile int *volatile vivp;
    int *ip = &v; // error: must use a pointer to volatile
    *ivp = &v; // ok: ivp is a pointer to volatile
    vivp = &v; // ok: vivp is a volatile pointer to volatile

}