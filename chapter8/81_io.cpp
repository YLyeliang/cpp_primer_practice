//
// Created by fiberhome on 2020/12/28.
//
#include <fstream> // file stream operation
#include "iostream"
#include "string"
#include "sstream" // string stream operation
#include "vector"

using namespace std;

// name xxx(series of phones)
struct PersonInfo {
    string name;
    vector<string> phones;
};

int main() {
    int ival;
    cin >> ival;
    auto old_state = cin.rdstate(); // remember the current state of cin
    cin.clear(); // make cin valid
    auto dd = &cin; //use cin
    cin.setstate(old_state); //now reset cin to its old state
    cout << "Hi" << endl; // write Hi and a newline, then flushes the buffer
    cout << "hi" << flush; // write hi, then flushes the buffer; add no data
    cout << "hi!" << ends; // write hi! and a null, then flushes the buffer

    cout << unitbuf; // all wirtes wil be flushed immediately
    cout << nounitbuf;  // returns to normal buffering

    cin.tie(&cout); // the library has tied the cin and cout for us.
    ostream *old_tie = cin.tie(nullptr); // cin is no longer tied
    // ties cin and cerr;
    cin.tie(&cerr); // reading cin flushes cerr, not cout
    cin.tie(old_tie); // reestablish normal tie between cin and cout

    // file system
    string file_name = "/Users/fiberhome/Downloads/Dockerfile";
    ifstream in(file_name);

    ofstream out;
    out.open(file_name + ".copy", ofstream::app);

    // sstream
    string line, word;
    vector<PersonInfo> people;
    while (getline(cin, line)) {
        PersonInfo info;
        istringstream record(line); // bind record to the line we just read
        record >> info.name; // read the name
        while (record >> word) // read the phone number
            info.phones.push_back(word); // store
        people.push_back(info); // append to people
    }

    for (const auto &entry: people) {
        ostringstream formatted, badNums;
        for (const auto &nums:entry.phones) {
            if (!valid(nums)) {
                badNums << " " << nums; // string in badNums
            } else
                formatted << " " << format(nums);
        }
        if (badNums.str().empty())  // no bad nums
            cout << entry.name << " " << formatted.str() << endl; // print
        else
            cerr << "input error: " << entry.name << " invalid number(s)" << badNums.str() << endl;
    }


    return 0;
}