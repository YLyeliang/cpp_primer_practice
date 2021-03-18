//
// Created by fiberhome on 2021/3/18.
//
#include "string"
#include "iostream"
#include "183.h"

using namespace std;


int main() {
    // example 1
    Panda ying_yang("ying yang");
    print(ying_yang);   // passes Panda to a reference to Bear
    highlight(ying_yang);   // passes Panda to a reference to Endangered
    cout << ying_yang << endl;

    // example 2
    Bear *pb = new Panda("ying_yang");
    pb->print();    // ok: Panda::print()
    pb->cuddle();   // error: not part of the Bear interface
    pb->highligh(); // error: ...
    delete pb;  // ok: Panda::~Panda()
    // when a panda is used via an Endangered pointer or reference, the Panda-specific and Bear portions of the Panda
    // interface are invisible:
    Endangered *pe = new Panda("ying_yang");
    pe->print(); // ok: Panda::print()
    pe->toes(); // error: not part of the Endangered interface
    pe->cuddle(); // error: not part of the Endangered interface
    pe->highlight(); // ok: Panda::highlight()
    delete pe; // ok: Panda::~Panda()

    // example 3
    void dance(const Bear&);
    void rummage(const Raccoon&);
    ostream& operator<<(ostream&, const ZooAnimal&);
    Panda ying_yang;
    dance(ying_yang); // ok: passes Panda object as a Bear
    rummage(ying_yang); // ok: passes Panda object as a Raccoon
    cout << ying_yang; // ok: passes Panda object as a ZooAnimal
}

