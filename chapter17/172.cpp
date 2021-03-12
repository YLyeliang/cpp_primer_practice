//
// Created by fiberhome on 2021/3/8.
//
#include <numeric>
#include "vector"
#include "tuple"
#include "iostream"
#include "algorithm"
#include "../chapter13/Sales_data.h"
#include "bitset"

using namespace std;
// The bitset type

int main() {
    // 172.1 Defining and initializing bitset
    // like array, has a fixed size
    // bitset<n> b;
    bitset<32> bitvec(1U);   // 32 bits; low-order bit is 1, remaining bits are 0
    // The bits starting at 0 are referred to as the low-order bits, ending at 31 are referred to high-order bits

    // Initializing a bitset from an unsigned value
    // when use an integral value as an initializer for a bitset, that xx is converted to unsigned long long.
    // if the size of bitset greater than unsigned long long, the remaining high-order bits are set to 0.
    // if ... less than ..., then only the low-order bits from the given value are used; the high-order bits beyond discard.
    // bitvec1 is smaller than the initializer, high-order bits from the initializer are discarded
    bitset<13> bitvec1(0xbeef);  // bits are 1111011101111
    // bitvec2 is bigger ..., high .. set to 0
    bitset<20> bitvec2(0xbeef);   // 00001011111011101111
    // on machines with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 ones
    bitset<128> bitvec3(~0ULL); // bits 0 ... are one; 63...127 are zero

    // Initializing a bitset from string
    bitset<32> bitvec4("1100"); // bits 2 and 3 are 1, others are 0
    string str("1111111000000011001101");
    bitset<32> bitvec5(str, 5, 4);    // four bits starting at str[5], 1100
    bitset<32> bitve6(str, str.size() - 4); // use last four

    // 172.2 Operations on bitset
    bool is_set = bitvec.any(); // ture, one bit is set
    bool is_not_set = bitvec.none();    // false, one bit is set
    bool all_set = bitvec.all(); // false, only one bit is set
    size_t onBits = bitvec.count(); // returns 1
    size_t sz = bitvec.size();  // 32
    bitvec.flip();  // reverses the value of all the bits in bitvec
    bitvec.reset(); // sets all the bits to 0
    bitvec.set();   // ... 1

    int i = 4;
    bitvec.flip(0); // reverses the value of the first bit
    bitvec.set(bitvec.size() - 1);  // turns on the last bit
    bitvec.set(0, 0);    // turns off the first bit
    bitvec.reset(i);    // turns off the ith bit
    bitvec.test(0); // returns false because the first bit is off

    bitvec[0] = 0;  // turns off the bit at position 0
    bitvec[31] = bitvec[0];   // set the last bit to the same as the first bit
    bitvec[0].flip();   // flip the value of the bit at position 0
    ~bitvec[0]; // equivalent operation to above
    bool b = bitvec[0];

    // Retrieving the value of a bitset
    // we can use these operations only if the size of the bitset is less than or equal to the corresponding size
    unsigned long ulong = bitvec3.to_ullong();
    cout << "ulong = " << ulong << endl;

    // bitset IO operators
    bitset<16> bits;
    cin >> bits; // read up to 16 1 or 0 characters from cin
    cout << "bits: " << bits << endl;

    // Using bits
    // a simple example to represent the pass/fail quiz results for 30 students
    bool status;
    // version using bitwise operators
    unsigned long quizA = 0;    // this value is used as a collection of bits
    quizA |= 1UL << 27; // indicate student number 27 passed    1UL = unsigned long 1
    status = quizA & (1UL << 27);   // check how student number 27 did
    quizA &= ~(1UL << 27);  // 27 failed
    // equivalent actions using the bitset library
    bitset<30> quizB;    // allocate one bit per student, all bits initialized to 0
    quizB.set(27);  // 27 passed
    status = quizB[27]; // check how 27 did
    quizB.reset(27);    // 27 failed



}