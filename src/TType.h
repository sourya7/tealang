
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
using std::string;

/*
 * 
 */

class TObj;

enum class TType {
    INTEGER = 1,
    DOUBLE,
    BOOLEAN,
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

class TObj {
private:
    TType type = TType::NIL;
    TValue* value = nullptr;
    TObj() {} 
public:
    static const TObj NIL;
    bool IsBool() { return false; }
    bool IsInteger() { return false; }
    bool IsString() { return false; }
    bool IsDouble() { return false; } 
    bool IsNil() { return false; }
    bool IsTrue() { return false; }

    TObj(long i){
        type = TType::INTEGER;
    }

    TObj(double d){
        type = TType::DOUBLE;
    }

    TObj(bool b){
        type = TType::BOOLEAN;
    }

    TObj(string* s){
        type = TType::STRING;
    }

    TObj(TObj* o){
        type = TType::OBJECT;
    }
};

#endif
