
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
using std::string;

/*
 * 
 */

class TObj;
enum TType {
    INTEGER = 1,
    REAL,
    BOOL,
    STRING,
    OBJECT,
    NIL
};

union TValue {
    long i;
    double r;
    bool b;
    string* str;
    TObj* object;
};

#endif
