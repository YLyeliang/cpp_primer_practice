//
// Created by yel on 2021/3/3.
//
#include "string"


using namespace std;


// these template types must be instantiated elsewhere in the program
extern template
class Blob<string>;

extern template int compare(const int &, const int &);

int main() {
    Blob<string> sa1, sa2;
    // Blob<int> and its initializer_list constructor instantiated in this file
    Blob<int> a1 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    Blob<int> a2(a1);   // copy constructor instantiated in this file
    int i = compare(a1[0], a2[0]);  // instantiation will appear elsewhere
}