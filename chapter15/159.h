//
// Created by yel on 2021/2/26.
//

#ifndef NOW_CODE_159_H
#define NOW_CODE_159_H

#include "string"
#include "iostream"
#include "memory"
#include "algorithm"
#include "../chapter12/chapter123.h"

using namespace std;
// Abstract base class
// four query types are not related to one another. Each class shares the same interface, which suggests that we'll
// define an abstract bse class to represent that interface.
// Query_base, will define eval and rep as pure virtual functions.
// BinaryQuery, to represent queries with two operands, such as operations in And and Or.
// Image see below
//                      Query_base
//                  //      ||      \\
//      Word Query      Not Query       BinaryQuery
//                                   //              \\
//                                  AndQuery        OrQuery

// Hiding a Hierarchy in an interface class
// user-level code won't use the inherited classes directly. Instead, we'll define an interface class named Query,
// which will hide the hierarchy.
// Users will create and manipulate Query_base objects only indirectly through operations on Query objects.
// We'll define 3 operators on Query objects
// & operator will generate a Query bound to a new AndQuery
// | ...    OrQuery
// ~ ...    NotQuery

// Understanding how these classes work

// abstract class acts as a base class for concrete query types; all members are private
class Query_base {
    friend class Query;

protected:
    using line_no = TextQuery::line_no; // used in the eval functions
    virtual ~Query_base() = default;

private:
    // eval returns the QueryResult that matches this Query
    virtual QueryResult eval(const TextQuery &) const = 0;

    // rep is a string representation of the query
    virtual std::string rep() const = 0;

};

// The Query Class
// interface class to manage the Query_base inheritance hierarchy
class Query {
    // these operators need access to the shared_ptr constructor
    friend Query operator~(const Query &);

    friend Query operator|(const Query &, const Query &);

    friend Query operator&(const Query &, const Query &);

public:
    Query(const string &);   // builds a new WordQuery
    // interface functions: call the corresponding Query_base operations
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }

    string rep() const { return q->rep(); }

private:
    Query(shared_ptr<Query_base> query) : q(query) {}

    shared_ptr<Query_base> q;
};

// The Query Output Operator
ostream &operator<<(ostream &os, const Query &query) {
    // Query::rep makes a virtual call through its Query_base pointer to rep()
    return os << query.rep();
}
// When we print a Query, the output operator calls the (public) rep member of class Query.
// That function makes a virtual call through its pointer member to the rep member of the object to which this Query points.
// Query andq = Query(sought1) & Query(sought2);
// cout<< andq << endl;
// the output operator calls Query::rep on andq.

// 159.3 The Derived Classes

// The WordQuery Class
class WordQuery : public Query_base {
    friend class Query; // Query uses the WordQuery constructor
    WordQuery(const string &s) : query_word(s) {}

    // concrete class: WordQuery defines all inherited pure virtual functions
    QueryResult eval(const TextQuery &t) const { return t.query(query_word); }

    string rep() const { return query_word; }

    string query_word;  // word for which to search
};

inline Query::Query(const string &s) : q(new WordQuery(s)) {}
// The constructor allocates a WordQuery and initializes its pointer member to point to that newly allocated object

// The NotQuery Class and the ~ operator
// The ~ operator generates a NotQuery, which holds a Query, which it negates:
class NotQuery : public Query_base {
    friend Query operator~(const Query &);

    NotQuery(const Query &q) : query(q) {}

    // concrete class: NotQuery defines all inherited pure virtual functions
    string rep() const { return "~(" + query.rep() + ")" }

    QueryResult eval(const TextQuery &) const;

    Query query;
};

inline Query operator~(const Query &operand) {
    return shared_ptr<Query_base>(new NotQuery(operand));
}
// the return statement is equivalent to
//shared_ptr<Query_base> tmp (new NotQuery(expr));
//return Query(tmp)

// The BinaryQuery Class
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, string s) :
            lhs(l), rhs(r), opSym(s) {}

    // abstract class: BinaryQuery doesn't define eval
    string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }

    Query lhs, rhs;
    string opSym;   // name of the operator
};
// Since BinaryQuery doesn't inherits a pure virtual. It is also an abstract base class, and we cannot create objects of
// BinaryQuery type.

// The AndQuery and OrQuery Classes and Associated Operators
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);

    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}

    // concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);

    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}

    // concrete class: OrQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs))
}

// 159.4 The eval functions
// we use the QueryResult from 12.3.

// OrQuery::eval
QueryResult OrQuery::eval(const TextQuery &text) const {
    // virtual calls through the Query members, lhs and rhs
    // the calls to eval return the QueryResult for each operand
    auto right = rhs.eval(text), left = lhs.eval(text);
    // copy the line numbers from the QueryResult for each operand
    auto ret_lines = make_shared<set<line_no>>(left.begin(), lef.end());
    // insets lines from the right-hand operand
    ret_lines->insert(right.begin(), right.end());

    // return the new QueryResult representing the union of lhs and rhs
    return QueryResult(rep(), ret_lines, left.get_file());
}

// AndQuery::eval
// returns the intersection of its operands' result sets
QueryResult AndQuery::eval(const TextQuery &text) const {
    // virtual calls through the Query operands to get result sets for the operands
    auto left = lhs.eval(text), right = rhs.eval(text);
    // set to hold the intersection of left and right
    auto ret_lines = make_shared<set<line_no>>();
    // writes the intersection of two ranges to a destination iterator
    // destination iterator in this call adds elements to ret
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

// NotQuery::eval
// returns the lines not in its operand's result set
QueryResult NotQuery::eval(const TextQuery &text) const {
    // virtual call to eval through the Query operand
    auto result = query.eval(text);
    // start out with an empty result set
    auto ret_lines = make_shared<set<line_no>>();
    // we have to iterate through the lines on which our operand appears
    auto beg = result.begin(), end = result.end();
    // for each line in the input file, if that line is not in result,
    // add that line number to ret_lines
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        // if we haven't processed all the lines in result
        // check whether this line is present
        if (beg == end || *beg != n)
            ret_lines->insert(n);   // if not in result, add this line
        else if (beg != end)
            ++beg;  // otherwise get the next line number in result if there is one
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}



#endif //NOW_CODE_159_H
