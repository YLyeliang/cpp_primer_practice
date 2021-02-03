//
// Created by fiberhome on 2021/2/2.
//

#ifndef NOW_CODE_CHAPTER123_H
#define NOW_CODE_CHAPTER123_H

#include "string"
#include "iostream"
#include "memory"
#include "vector"
#include <utility>

#include "string"
#include "fstream"
#include "map"
#include "set"
#include "sstream"

using namespace std;

string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

class QueryResult { // declaration needed for return type in the query function
    friend ostream &print(ostream &, const QueryResult &);

public:
    using line_no = vector<string>::size_type;

    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :
            sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {}

private:
    string sought;  // word this query represents
    shared_ptr<set<line_no>> lines; // lines it's on
    shared_ptr<vector<string>> file; // input file
};

ostream &print(ostream &os, const QueryResult &qr) {
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << endl;
    // print each line in which the word appeared
    for (auto num: *qr.lines) // for every element in the set
        // don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}


class TextQuery {
public:
    using line_no = vector<string>::size_type;

    explicit TextQuery(ifstream &);

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

QueryResult TextQuery::query(const string &sought) const {
    // we'll return a pointer to this set if we don't find sought
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // use find and not a subscript to avoid adding words to wm
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found
    else
        return QueryResult(sought, loc->second, file);
}

#endif //NOW_CODE_CHAPTER123_H
