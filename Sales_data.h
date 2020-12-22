//
// Created by fiberhome on 2020/11/13.
//

#ifndef NOW_CODE_SALES_DATA_H
#define NOW_CODE_SALES_DATA_H

#include "string"

struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

#endif //NOW_CODE_SALES_DATA_H
