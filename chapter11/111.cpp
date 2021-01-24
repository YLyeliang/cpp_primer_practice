//
// Created by yel on 2021/1/23.
//

#include "iostream"
#include "vector"
#include "list"
#include "map"
#include "set"
#include "string"

using namespace std;

int main() {


    // Erasing Elements
    // multimap
    multimap<string, string> authors;
    authors.insert({"Barth,John", "Sot-Weed Factor"});
    authors.insert({"Barth,John", "Lost in the Funhouse"});
    cout << authors.size() << endl;
    for (auto &pair: authors)
        cout << pair.first << pair.second << endl;

    auto cnt = authors.erase("Barth,John");
    cout << authors.size() << endl;
    for (auto &pair: authors)
        cout << pair.first << pair.second << endl;


    // Subscripting a map
    map<string, size_t> word_count; // empty map
    word_count["Anna"] = 1;  // "" for string , '' for char
    // when we subscript a map, we get a mapped_type object; deference a map iterator, .. value_type

    // Accessing Elements
    // Provide various way to access elements in associative container:
    // c.find(k)    return an iterator to the (first) element with key k,or the off-the-end when not found
    // c.count(k)   the number of elements with k. for ... with unique keys, the result is 0 or 1.
    // c.lower_bound(k) an iterator to the first element with key not less than k.
    // c.upper_bound(k) ... greater than k.
    // c.equal_range(k) return a pair of iterators denoting the elements with key k. If k is not present, both members are c.end().
    set<int> iset = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    auto end = iset.end();
//    cout << *end << endl; // error: can't deference the end.
    auto i = iset.find(1); // iterator refers to element with key ==1
    i = iset.find(11); // iset.end()
    auto c = iset.count(1); // 1
    c = iset.count(11); // 0

    // Using find instead of subscript for maps
    // because subscript will inserts an element when that key is not in container.
    if (word_count.find("foobar") == word_count.end())
        cout << "foobar is not in the map" << endl;

    // Finding Elements in a multimap or multiset
    string search_item("Alain de Botton"); // author we'll look for
    auto entries = authors.count(search_item); // number of elements
    auto iter = authors.find(search_item); // first entry for this author
    // loop through the number of entries there are for this author
    while (entries) {
        cout << iter->second << endl; // print each title
        ++iter; // advance to the next title
        --entries; // keep track of how many we've printed
    }

    // A Different, Iterator-Oriented Solution
    // Alternatively, we can solve by using lower_bound and upper_bound.
    for (auto beg = authors.lower_bound(search_item),
                 end = authors.upper_bound(search_item);
         beg != end; ++beg)
        cout << beg->second << endl; // print each title

    // The equal_range Function
    // return a pair of iterator, including begin and the one past the last.
    for (auto pos = authors.equal_range(search_item);
         pos.first != pos.second; ++pos.first)
        cout << pos.first->second << endl;

    // A Word Transformation Map
    // See file 113_program.cpp

    // Using an Unordered Container

    // count occurences, but the words won't be in alphabetical order
    unordered_map <string, size_t> word_count2;
    string word;
    while (cin >> word)
        ++word_count2[word]; // fetch and increment the counter for word
    for (const auto &w:word_count2) // for each element in the map
        // print the results
        cout << w.first << " occurs " << w.second
             << ((w.second > 1) ? " times" : " time") << endl;



}