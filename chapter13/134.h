//
// Created by yel on 2021/2/8.
//

#ifndef NOW_CODE_134_H
#define NOW_CODE_134_H

#include "string"
#include "set"

using namespace std;

class Message {
    friend class Folder;

public:
    // folder is implicitly initialized to the empty set
    explicit Message(const string &str = "") : contents(str) {}

    // copy control to manage pointers to this message
    Message(const Message &);    // copy constructor
    Message &operator=(const Message &);  // copy assignment
    ~Message(); // destructor
    // add/remove this Message from the specified Folder's set of messages
    void save(Folder &);

    void remove(Folder &);

    void swap(Message &lhs, Message &rhs) {
        using std::swap;    // not striclty needed in this case, but good habit
        // remove pointers to each Message from their respective Folders
        for (auto f:lhs.folders)
            f->remMsg(&lhs);
        for (auto f:rhs.folders)
            f->remMsg(&rhs);
        // swap the contents and Folder pointer sets
        swap(lhs.folders, rhs.folders);  // uses swap(set&, set&)
        swap(lhs.contents, rhs.contents);   // swap(string&, string&)
        // add pointers to each Message to their respective Folders
        for (auto f: lhs.folders)
            f->addMsg(&lhs);
        for (auto f:rhs.folders)
            f->addMsg(&rhs);
    }


private:
    string contents;    // actual message text
    set<Folder *> folders;   // Folders that have this Message
    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message &);

    // remove this message from every folder in folders
    void remove_from_Folders();

};

void Message::save(Folder &f) {
    folders.insert(&f); // add the given Folder to our list of Folders
    f.addMsg(this); // add this Message to f's set of Messages
}

void Message::remove(Folder &f) {
    folders.erase(&f); // take the given Folder out of our list of Folders
    f.remMsg(this); // remove this Message to f's set of Messages
}

// copy control for Message class
void Message::add_to_Folders(const Message &m) {
    for (auto f: m.folders) // for each Folder that holds m
        f->addMsg(this);    // add a pointer to this Message to that Folder
}

Message::Message(const Message &m) :
        contents(m.contents), folders(m.folders) {
    add_to_Folders(m); // add this Message to the Folders that point to m
}

// remove this Message from the corresponding folders
void Message::remove_from_Folders() {
    for (auto f: folders):
    f->remMsg(this);
}

// destructor
Message::~Message() {
    remove_from_Folders();
}

// Message Copy-assignment Operator
Message &Message::operator=(const Message &rhs) {
    // handle self-assignment by removing pointers befor inserting them
    remove_from_Folders();  // update existing folders
    contents = rhs.contents;  // copy message contents from rhs
    folders = rhs.folders;    // copy Folder pointers from rhs
    add_to_Folders(rhs);    // add this Message to those Folders
    return *this;
}

// a swap function for Message


#endif //NOW_CODE_134_H
