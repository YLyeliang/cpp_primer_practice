//
// Created by fiberhome on 2021/1/14.
//

#include "numeric"
#include "vector"
#include "list"
#include "string"
#include "algorithm"
#include "iostream"

using namespace std;

// predicate
// in sort, to take binary predicates. The function we defined must in place of < operation to compare.
bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

// lambda Expression
void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5, 6};
    // the third argument has an important implication. the elements in sequence must match or be convertible to
    // the type of the third argument.
    accumulate(vec.cbegin(), vec.cend(), 0); // accumulation

    // string concatenation
    vector<string> v = {"as", "a", "world"};
    string sum = accumulate(v.cbegin(), v.cend(), string(""));
    //string sum = accumulate(v.cbegin(), v.cend(), ""); error: the char* have no + operation.

    // note: it's best to use cbegin & cend() with read-only algorithm.

    // algorithm: equal
    // determine whether two sequences hold the same values
    vector<int> roster1 = {1, 2, 3, 4, 5, 6};
    vector<int> roster2 = {1, 2, 3, 4, 5, 6, 7, 8};
    equal(roster1.cbegin(), roster1.cend(),
          roster2.cbegin()); // roster2 should have at least as many elements as roster1

    // algorithm that write container elements
    // fill
    fill(vec.begin(), vec.end(), 0); // reset each element to 0
    fill(vec.begin(), vec.begin() + vec.size() / 2, 10);

    // Algorithms do not check write operations
    fill_n(vec.begin(), vec.size(), 0); // reset all to 0
    // fill_n assume that there are at least vec.size() elements in vec
    fill_n(vec.begin(), 100, 0); // disaster: attempts to write to 100 (non-exists) elements in vec

    // back_inserter
    // takes a reference to a container and return an insert iterator, when assign through iterator, it calls
    // push_back.
    auto it = back_inserter(vec); // assigning through it adds elements to vec
    *it = 42; // vec now has one element with value 42

    // predicate
    vector<string> words = {"123", "4214", "1"};
    sort(words.begin(), words.end(), isShorter);

    // sorting algorithms
    elimDups(words); // put words in alphabetical order and remove duplicates
    // resort by length, maintaining alphabetical order among words of the same length
    stable_sort(words.begin(), words.end(), isShorter);

    // lambda Expression
    // introducing lambdas
    // we can pass any kind of callable object to algorithm
    // lambda can be thought of as an an unnamed, inline function.
    // [capture list] (parameters list) -> return type {function body}
    // capture list is an (often empty) list of local variables defined in the enclosing function.
    auto f = [] { return 42; };
    cout << f() << endl;

    // passing arguments to a lambda
    // same like isShorter
    stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
        return a.size() < b.size();
    });

    // using capture list
    string::size_type sz;
    [sz](const string &a)
    {return a.size()>=sz;};

}
