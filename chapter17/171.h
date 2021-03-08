//
// Created by fiberhome on 2021/3/8.
//

#ifndef NOW_CODE_171_H
#define NOW_CODE_171_H

#include <numeric>
#include "vector"
#include "tuple"
#include "iostream"
#include "algorithm"
#include "../chapter13/Sales_data.h"

using namespace std;

// matches has three members: an index of store and iterators into that store's vector
typedef tuple<vector<Sales_data>::size_type,
        vector<Sales_data>::const_iterator,
        vector<Sales_data>::const_iterator> matches;

// files holds the transactions for every store
// findBook returns a vector with an entry for each store that sold the given book
vector<matches>
findBook(const vector<vector<Sales_data>> &files, const string &book) {
    vector<matches> ret; // initially empty
    // for each store find the range of matching books, if any
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        // find the range of Sales_data that have the same ISBN
        // equal_range returns a pair denoting ranges having given book, which same as associative container c.equal_range()
        auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (found.first != found.second)  // this store had sales
            // remember the index of the store and the matching range
            ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second));
    }
    return ret;
}

// Using a tuple returned by a function
// we'll report the total sales results for each store that has a matching sale
void reportResults(istream &in, ostream &os, const vector<vector<Sales_data>> &files) {
    string s;
    while (in >> s) {
        auto trans = findBook(files, s); // stores that sold this book
        if (trans.empty()) {
            cout << s << " not found in any store" << endl;
            continue;
        }
        for (const auto &store:trans)
            cout << "Store " << get<0>(store) << " Sales: " << accumulate(get<1>(store), get<2>(store), Sales_data(s))
                 << endl;
    }
}

#endif //NOW_CODE_171_H
