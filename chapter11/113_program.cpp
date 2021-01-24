//
// Created by yel on 2021/1/23.
//

#include "iostream"
#include "vector"
#include "list"
#include "map"
#include "set"
#include "string"
#include "fstream"
#include "sstream"

using namespace std;


// build map
map<string, string> buildMap(ifstream& map_file){
    map<string, string> trans_map;
    string key; // a word to transform
    string value; // phrase to use instead
    // read the first word into key and the rest of the line into value
    // ifstream read one word by space each time.
    while (map_file>>key &&  getline(map_file,value))
        if (value.size()>1) // check that there is a transformation
            trans_map[key] = value.substr(1); // skip leading space
        else
            throw runtime_error("no rule for " + key);
    return trans_map;
}

// generating a transformation
const string & transform(const string &s, const map<string,string> &m)
{
    // the actual map work; this part is the heart of the program
    auto map_it = m.find(s);
    // if this word is in the transformation map
    if (map_it!=m.cend())
        return map_it->second; // use the replacement word
    else
        return s; // other return the original unchanged
}


// word_transform. Given two files:1. file contains rules that map abbrev to word.
// 2. file contains string needed to be transformed
void word_transform(ifstream &map_file,ifstream &input)
{
    auto trans_map = buildMap(map_file); // store the transformations
    string text;
    while (getline(input,text)){ // read a line ofn input
        istringstream stream(text); // read each word

        string word;
        bool firstword=true; // controls whether a space is printed
        while (stream >>word) {
            if (firstword)
                firstword = false;
            else
                cout<< " "; // print a space between words
            // transform returns its first argument or its transformation
            cout<< transform(word,trans_map); // print the output
        }
        cout<<endl; // done with this line of input
    }
}

int main() {
    string file1="../test_files/11_word_transformation_1";
    string file2="../test_files/11_word_transformation_2";
    ifstream map_file(file1);
    ifstream input(file2);
    word_transform(map_file,input);
}
