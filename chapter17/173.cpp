//
// Created by fiberhome on 2021/3/9.
//

#include "regex"
#include "string"
#include "vector"
#include "iostream"

using namespace std;

// Regular expressions  正则表达式
// A regular expression is a way of describing a sequence of characters
// regex_match regex_search regex_replace

bool valid(const smatch &m) {
    // if there is an open parenthesis before the area code
    if (m[1].matched)
        // the area code must followed by a close parenthesis
        // and followed immediately by the rest of the number or a space
        return m[3].matched
               && (m[4].matched == 0 || m[4].str() == " ");
    else
        // then there can't be a close after the area code
        // the delimiters between the other two components must match
        return !m[3].matched
               && m[4].str() == m[6].str();
}

int main() {
    // 173.1 Using the regular expression library
    // as a example, we'll look for words that violate a well-known spelling rule of thumb, "i before e except after c"
    // find the characters ei that follow a character other than c
    string pattern("[^c]ei");
    // we want the whole word in which our pattern appears
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);   // construct a regex to find pattern
    smatch results; // define an object to hold the results of a search
    // define a string that has text that does and doesn't match pattern
    string test_str = "receipt freind theif receive";
    // use r to find a match to pattern in test_str
    if (regex_search(test_str, results, r))   // if there is a match
        cout << results.str() << endl;  // print the matching word
    // [^c] means not a c. By default, the regex objects is ECMAScript, [[:alpha:]] matches any alphabetic character
    // the symbol + and * signify that "one or more" or "zero or more"

    // Specifying Options for regex object
    // one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
    regex r2("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
    string filename;
    while (cin >> filename) {
        if (regex_search(filename, results, r2))
            cout << results.str() << endl;
        if (filename == "end") break;
    }  // print the current match
    // the dot(.) usually matches any character,we must use \\ to present \ in C++, since \ is still a special character in c++.

    // Errors in specifying or using a regular expression
    // If a regex written in wrong way, a regex_error will be thrown.
    // for example, we might inadvertently omit a bracket in a pattern
    try {
        // error: missing close bracket after alnum; the constructor will throw
        regex r3("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);
    } catch (regex_error e) {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }
    // system print: The expression contained mismatched [ and ].
    // code: 5
    // if you use a regular expression in a loop, you should create it outside the
    // loop rather than recompiling it on each iteration.

    // Regular expression classes and the input sequence type
    // smatch represents string input sequences; cmatch, character array ...; wsmatch, wide string(wstring);
    // wcmatch, ...
    // input sequence type and re library type must match
    regex r4("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
    if (regex_search("myfile.cc", results, r4)) // error: char* input
        cout << results.str() << endl;
    // should be written as below
    cmatch c_results;
    if (regex_search("myfile.cc", c_results, r4))
        cout << c_results.str() << endl;

    // 173.2 The match and regex iterator types
    // the example "i before e ..." only print the first match. We can use sregex_iterator to get all.

    // using an sregex_iterator
    // still the "i before ..." example
    regex r5(pattern, regex::icase); // we'll ignore case in doing the match
    // it will repeatedly call regex_search to find all matches in the file
    for (sregex_iterator it(filename.begin(), filename.end(), r), end_it; it != end_it; ++it)
        cout << it->str() < , endl; // matched word
    // when we define it, the sregex_iterator constructor calls sregex_search to position it on the first match.
    // The empty end_it, acts as the off-the-end iterator

    // using the matching data
    // In addition to letting us to print the part of the input string that was matched, some operations are used.
    // smatch operations: ready() size() empty() prefix() suffix() format(...)
    // ssub_match, let us to see the context of a match
    for (sregex_iterator it(filename.begin(), filename.end(), r), end_it; it != end_it; ++it) {
        auto pos = it->prefix().length(); // size of the prefix
        pos = pos > 40 ? pos - 40 : 0;  // we want up to 40 characters
        cout << it->prefix().str().substr(pos)    // last part of the prefix
             << "\n\t\t>>> " << it->str() << "<<<\n"    // matched word
             << it->suffix().str().substr(0, 40) // first part of the suffix
             << endl;
    }
    //                                                             it->str()
    //                                                                |
    //                                                                V
    // when it refer to the ith smatch object: it->prefix().str() xxxeixxx  it->suffix().str()
    // when call prefix, returns an ssub_match that represents the part of filename ahead of current match

    // 173.3 Using subexpressions
    // a subexpression is a part of the pattern that itself has meaning
    // r has two subexpressions: the first is th part of the file name before the period
    // the second is the file extension
    regex r6("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
    // ([[:alnum:]]+), which is a sequence of one or more characters
    // (cpp|cxx|cc), which is the file extension
    // we can also rewrite 173.1 to print just the file name
    if (regex_search(filename, results, r6))
        cout << results.str(1) << endl; // print the first subexpression
    // the first submatch, which is at position 0, represents the match for the entire pattern
    // for example, file name is foo.cpp. results.str(0): foo.cpp results.str(1):foo results.str(2):cpp

    // Subexpression for data validation
    // one common use for subexpression is to validate data that must match a specific pattern.
    // For example, U.S phone numbers have ten digits, consisting of an area code and a seven-digits local number.
    // The area code is often, but not always, enclosed in parentheses. The remaining seven digits can be separated by
    // a dash, a dot, or a space; or not separated at all.
    // we'll do two steps process to validate the data:
    // 1. use a regular expression to find sequences that might be phone numbers
    // 2. call a function to complete the validation
    // some characteristics for ECMAScript regular-expression language:
    // \{d}: single digit.  \{d}{n}: a sequence of n digits
    // A collection of characters inside square brackets allow a match to any of these. [-. ] matches dash, dot and space
    // A component followed by ? is optional. \{d}{3}[-. ]?\{d}{4} matches three digits followed by an optional dash,
    // period, or space, followed by four digits. would match 555-0131 555.0132 or 5550131
    // represent the parentheses as \(
    // Because \ is a special character in c++, each \ appears in the pattern, must use \\ to represent the \

    // our overall expression has seven subexpression: (ddd) separator ddd separator dddd
    // subexpression 1,3,4 and 6 are optional; 2,5, and 7 hold the number
    string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    regex r7(phone);
    smatch m;
    string s;
    // read each record from the input file
    while (getline(cin, s)) {
        // for each matching phone number
        for (sregex_iterator it(s.begin(), s.end(), r7), end_it; it != end_it; ++it)
            // check whether the number's formatting is valid
            if (valid(*it))
                cout << "valid: " << it->str() << endl;
            else
                cout << "not valid: " << it->str() << endl;
    }

    // using the submatch operations
    // write valid function, see func before main.

    // using regex_replace
    // find a given sequence and replace that with another one.
    string fmt = "$2.$5.$7";   // reformat numbers to ddd.ddd.dddd
    string number = "(908) 555-1800";
    cout << regex_replace(number, r7, fmt) < , endl;    // output 908.555.1800

    // Replacing only part of the input sequence
    // for example, we have a file of names like this:
    // morgan (201) 555-2368 862-555-0123
    // drew (973)555.0130
    // lee (609) 555-0132 2015550175 800.555-0000
    // we want to tranform like this:
    // morgan 201.555.2368 862.555.0123
    // drew 973.555.0130
    // lee 609.555.0132 201.555.0175 800.555.0000
    while (getline(cin, s))
        cout << regex_replace(s, r7, fmt) << endl;

    // Flags to control matches and formatting
    using std::regex_constants::format_no_copy;
    using namespace std::regex_constants;

    // using format flags
    // generate just the phone numbers: use a new format string
    string fmt2 = "$2.$5.$7 ";
    // tell regex_replace to copy only the text that it replaces
    cout << regex_replace(s, r7, fmt2, format_no_copy) << endl;
    // results: 201.555.2368 862.555.0123
    // 973.555.0130
    // 609.555.0132 201.555.0175 800.555.0000



}


