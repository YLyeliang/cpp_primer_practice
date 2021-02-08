//
// Created by fiberhome on 2021/2/2.
//

#include "string"
#include "iostream"
#include "memory"
#include "list"
#include "vector"
#include "string"
#include "fstream"
#include "map"
#include "set"

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


void runQueries(ifstream &infile) {
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile); // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true) {
        cout << "enter word to look for, or press q to quit:";
        string s;
        // stop if we hit an end-of-file on the input or a 'q' is entered
        if (!(cin >> s) || s == "q") break;
        // run the query and print the results
        print(cout, tq.query(s)) << endl;

    }


}


int main() {

}
