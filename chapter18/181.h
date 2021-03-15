//
// Created by fiberhome on 2021/3/15.
//

#ifndef NOW_CODE_181_H
#define NOW_CODE_181_H

#include "string"
#include "../chapter16/161.h"

using namespace std;

// Not define constructor and data member in 161.h, so omit the error
template<typename T>
Blob<T>::Blob(initializer_list<T> il) try :data(make_shared<vector<T>>(il)) {
    // empty body
} catch (const bad_alloc &e) {
    handle_out_of_memory(e);
}

#endif //NOW_CODE_181_H
