//
// Created by fiberhome on 2021/3/25.
//

#ifndef NOW_CODE_195_H
#define NOW_CODE_195_H

#include "string"
#include "iostream"
#include "memory"
#include "set"
#include "vector"

using namespace std;

// Nested Classes

// Declaring a Nested class
class TextQuery {
public:
    class QueryResult;  // nested class to be defined later
    // other member as in 123.2
    using line_no = vector<string>::size_type;

    QueryResult query(const string &) const;

private:
    shared_ptr<vector<string>> file; // input file
    // map of each word to the set of the lines in which that word appears
    map <string, shared_ptr<set<line_no>>> wm;
};

// Defining a nested class outside of the enclosing class
class TextQuery::QueryResult {
    // in class scope, we don't have to qualify the name of the QueryResult parameters
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:


    // no need to define QueryResult::line_no; a nested class can use a member
    // of its enclosing class without needing to qualify the member's name
    QueryResult(std::string, std::shared_ptr<std::set<line_no>>,
                std::shared_ptr<std::vector<std::string>>
    );

private:
    string sought;  // word this query represents
    shared_ptr<set<line_no>> lines; // lines it's on
    shared_ptr<vector<string>> file; // input file
};
// The only change we made is no longer define a line_no in QueryResult.

// Defining the members of the nested class
TextQuery::QueryResult::QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
                                    std::shared_ptr<std::vector<std::string>> f) :
        sought(s), lines(p), file(f) {}

// Nested class static member definition
// If QueryResult declared a static member, its definition would appear outside the scope of the TextQuery
int TextQuery::QueryResult::static_mem = 1024;

// Name looking in Nested class scope
// nested class has additional enclosing class scopes to search
// return type must indicate that QueryResult is now a nested class
TextQuery::QueryResult
TextQuery::query(const string &sought) const {
    // we'll return a pointer to this if we don't find sought
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found
    else
        return QueryResult(sought, loc->second, file);
}


#endif //NOW_CODE_195_H
