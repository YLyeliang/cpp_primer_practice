//
// Created by fiberhome on 2020/11/18.
//
#include "iostream"
#include "vector"
#include "string"

using namespace std;

int main() {
    string text = "abcdefghijklmnopqrstuvwxyz";
    auto beg = text.begin(), end = text.end();
    auto mid = text.begin() + (end - beg) / 2; // midpoint
    char sought = 'v';
    int n = 0;
    while (mid != end && *mid != sought) {
        n++;
        if (sought < *mid)
            end = mid - 1;
        else
            beg = mid + 1;
        mid = beg + (end - beg) / 2;
    }
    cout << n << endl;

}
