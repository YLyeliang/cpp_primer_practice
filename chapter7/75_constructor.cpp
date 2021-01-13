//
// Created by fiberhome on 2020/12/23.
//
#include "Sales_data.h"
#include "string"

using namespace std;

int main() {
    // implicit class-type conversion
    string null_book = "9-99-999";
    Sales_data item;
    item.combine(null_book);
    item.combine(string("9999"));

}
