//
// Created by fiberhome on 2021/2/2.
//

#ifndef NOW_CODE_CHAPTER123_H
#define NOW_CODE_CHAPTER123_H

#include "string"
#include "iostream"
#include "memory"
#include "vector"
#include "string"
#include "fstream"
#include "map"
#include "set"
#include "sstream"

using namespace std;

class QueryResult; // declaration needed for return type in the query function
class TextQuery {
public:
    using line_no = vector<string>::size_type;

    TextQuery(ifstream &);

    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> file; // input file
    // map of each word to the set of the lines in which that word appears
    map<string, shared_ptr<set<line_no>>> wm;
};

// The TextQuery Constructor
// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream &is) : file(new vector<string>) {
    string text;
    while (getline(is, text)) { // for each line in the file
        file->push_back(text); // remember this line of text
        int n = file->size() - 1; // the current line number
        istringstream line(text); // separate the line into words
        string word;
        while (line >> word) {    // for each word in that line
            // if word isn't already in wm, subscripting adds a new entry
            auto &lines = wm[word]; // lines is a shared_ptr
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new set<line_no>); // allocate new set
            lines->insert(n);   // insert this line number
        }
    }
}

#endif //NOW_CODE_CHAPTER123_H
