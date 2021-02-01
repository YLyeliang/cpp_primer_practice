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
using namespace std::placeholders;

string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

// predicate
// in sort, to take binary predicates. The function we defined must in place of < operation to compare.
bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

// lambda Expression
// capture by reference:
void biggies(vector<string> &words, vector<string>::size_type sz, ostream &os = cout, char c = ' ') {
    elimDups(words); // put words in alphabetical order and remove duplicates
    // sort words by size,
    stable_sort(words.begin(), words.end(),
                [](const string &a, const string &b) { return a.size() < b.size(); });
    // get an iterator to the first elements whose size() >= sz.
    auto wc = find_if(words.begin(), words.end(),
                      [sz](const string &a) { return a.size() >= sz; });
    // compute the number of elements with size >=sz
    auto count = words.end() - wc;

    // print words of the given size or longer, each one followed by a space
    for_each(wc, words.end(),
             [](const string &s) { cout << s << " "; });
    // capture by reference sometimes necessary, example like below
    for_each(wc, words.end(),
             [&os, c](const string &s) { os << s << c; });
    cout << endl;
}

// capture  by value: lambda
void func1() {
    size_t v1 = 42; // local variables
    // copies v1 into the callable object named f
    auto f = [v1] { return v1; };
    v1 = 0;
    auto i = f(); // j is 42; f stored a copy of v1 when we created it.
}

void func2() {
    size_t v1 = 41;
    // the object of f2 contains a reference to v1
    auto f2 = [&v1] { return v1; };
    v1 = 0;
    auto j = f2(); // j is 0; f2 refers to v1; it doesn't store it.
}

// mutable lambda
// by default, a lambda may not the change value of a variable that it copies by value.
// then must follow the param list with keyword mutable
void func3() {
    size_t v1 = 41;
    // f can change the value of the variables it captures
    auto f = [v1]() mutable { return ++v1; };
    v1 = 0;
    auto j = f(); // j is 42
}

// While, a variable whether can be changed captured by reference only depends on it refers to const or non-const.

// Binding argument
bool check_size(const string &s, string::size_type sz) {
    return s.size() >= sz;
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
    [sz](const string &a) { return a.size() >= sz; };

    // calling find_if
    // get an iterator to the first element whose size >= sz.
    auto wc = find_if(words.begin(), words.end(),
                      [sz](const string &a) { return a.size() >= sz; });
    // compute the number of elements with size >= sz.
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
         << "of length" << sz << "or longer" << endl;

    // for_each Algorithm
    // print words of the given size or longer, each one followed by a space
    for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
    cout << endl;

    // putting it all together
    // see function biggies

    // Lambda captures and Returns
    // there are [], [names] [&] [=] [&,identifier_list] [=,reference_list]
    // capture by value: see func1 above the main()

    // Capture by reference: see func2

    // implicit Captures:
    wc = find_if(words.begin(), words.end(),
                 [=](const string &s) { return s.size() >= sz; });

    // specifying the return type of lambda
    vector<int> vi = {-1, -2, -3, 1};
    transform(vi.begin(), vi.end(), vi.begin(), [](int i) { return i < 0 ? -i : i; });
    // when we need to define a return type, we must use a trailing return type
    transform(vi.begin(), vi.end(), vi.begin(), [](int i) -> int { if (i < 0)return -i; else return i; });


    // Binding Arguments
    // general form of a call to bind is:
    auto newCallble = bind(callable, arg_list);
    // The arg_list may includes names of form _n, where n is an integer.
    // They stand 'in place of' the arguments that will be passed to newCallable.
    // Binding the sz param of check_size

    auto check6 = bind(check_size, _1, 6);

    // using placeholder Names



}
