//
// Created by fiberhome on 2020/12/24.
//

#ifndef NOW_CODE_76_STATIC_CLASS_MEMBER_H
#define NOW_CODE_76_STATIC_CLASS_MEMBER_H

#include "string"

// The static members of a class exist outside any object
// static member functions are not bound to any object
class Account {
public:
    void calculate() { amount += amount * interestRate; }

    static double rate() { return interestRate; }

    static void rate(double);

private:
    static constexpr int period = 30;
    double daily_tbl[period];
    std::string owner;
    double amount;
    static double interestRate;

    static double initRate();
};

void Account::rate(double newRate) {
    interestRate = newRate;

}

double Account::interestRate = initRate();

#endif //NOW_CODE_76_STATIC_CLASS_MEMBER_H
