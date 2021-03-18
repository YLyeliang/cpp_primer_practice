//
// Created by fiberhome on 2021/3/18.
//

#ifndef NOW_CODE_183_H
#define NOW_CODE_183_H

#include "string"
#include "iostream"
#include "memory"

using namespace std;

// Multiple and Virtual Inheritance
// Multiple inheritance is the ability to derive a class from more than one direct base class.
// use example of a zoo animal hierarchy.

// 183.1 Multiple inheritance
class ZooAnimal {
};

class Endangered {
};

class Bear : public ZooAnimal {
    Bear() = default;
};

class Panda : public Bear, public Endangered {
public:
    Panda(const string &s) : Bear(s), Endangered(s) {}
};

// Multiply Derived classes inherit state from each base class

// Derived constructors initialize all base classes
// explicitly initialize both base classes
Panda::Panda(string name, bool onExhibit) : Bear(name, onExhibit, "Panda"), Endangered(Endangered::critical) {}

// implicitly uses the Bear default constructor to initialize the Bear subobject
Panda::Panda() : Endangered(Endangered::critical) {}

// Inherited constructors and multiple inheritance
struct Base1 {
    Base1() = default;

    Base1(const string &);

    Base1(shared_ptr<int>);
};

struct Base2 {
    Base2() = default;

    Base2(const string &);

    Base2(int);
};

// error: D1 attempts to inherit D1::D1(const string&) from both base classes
struct D1 : public Base1, public Base2 {
    using Base1::Base1; // inherit constructors from Base1
    using Base2::Base2; // inherit constructors from Base2
};

// A class that inherits the same constructor from more than one base class must define its own version of that constructor:
struct D2 : public Base1, public Base2 {
    using Base1::Base1;
    using Base2::Base2;

    // D2 must define its own constructor that takes a string
    D2(const string &s) : Base1(s), Base2(s) {}

    D2() = default;
};

// Destructors and multiple inheritance
// Destructors are always invoked in the reverse order from which the constructors are run. ~Panda, ~Endangered,~Bear,~ZooAnimal

// Copy and move operations for multiply derived classes

// 183.2 Conversions and multiple base classes
// under single inheritance, a pointer or reference to a derived class can be converted automatically to a pointer or
// a reference to an accessible base class
// The same holds true with multiple inheritance. a pointer or reference to ZooAnimal, Bear, or Endangered can be bound to
// Panda object
// operations that take references to base classes of type Panda
void print(const Bear &);

void highlight(const Endangered &);

ostream &operator<<(ostream &, const ZooAnimal &);
// see example 1

// The compiler makes no attempt to distinguish between base classes in terms of a derived-class conversion. For example
// void print(const Bear &);
// void print(const Endangered &);
// Panda ying_yang("ying yang");
// print(ying_yang);         // would be wrong: ambiguous

// Lookup based on type of pointer or reference
// see example 2

// 183.3 Class scope under multiple inheritance
// In our example, if we use a name through a Panda object, pointer, or reference, both the Endangered and the Bear/ZooAnimal
// subtrees are examined in parallel.  If the name is found in more than one subtree, then the use of the name is ambiguous
// example, if both ZooAnimal and Endangered define a member named max_weight, and panda doesn't.
// double d = ying_yang.max_weight()        would be an error
// can be avoided by specifically indicate which version to use -ZooAnimal::.. or ..
// we should give its own version:
double Panda::max_weight() const {
    return std::max(ZooAnimal::max_weight(),
                    Endangered::max_weight());
}

// 183.4 Virtual Inheritance
// a class can inherit from the same class more than once.
// As a example, the istream and ostream classes each inherit from a common abstract base class named basic_ios.
// That class holds the stream's buffer and manages the stream's condition state.
// The class iostream, which can both write and read, inherits directly from both istream and ostream, it inherits basic_ios twice
// By default, a derived object contains a separate subpart corresponding to each class in its derivation chain.
// This default doesn't work for iostream. Since it wants to use the same buffer for both reading and writing.
// To solve this,
// virtual inheritance lets a class specify that it is willing to share its base class.
// The shared base-class subobject is called a virtual base class.

// A different panda class
// panda is inherited from three: Endangered, Bear and Racoon. Both Bear and Raccoon inherited from ZooAnimal

// using a virtual base class
class Raccoon : public virtual ZooAnimal {
};

class Bear : public virtual ZooAnimal {
};

class Panda : public Bear,
              public Raccoon, public Endangered {
};

// Normal Conversions to Base are supported
// see example 3

// Visibility of virtual base-class members

// 183.5 Constructors and virtual inheritance


#endif //NOW_CODE_183_H
