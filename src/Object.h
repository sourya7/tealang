
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
using std::string;

/*
 * 
 */

class Object;
class Token;

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
    double d;
    bool b;
    char* s;
    Object* o;

    TValue() {}
    TValue(long v) : i(v) {}
    TValue(double v) : d(v) {}
    TValue(bool v) : b(v) {}
    TValue(char* v) : s(v) {}
    TValue(Object* v) : o(v) {}
};

class Object {
private:
    TType type = TType::NIL;
    TValue* value = nullptr;
    Object() { }
public:
    static const Object NIL;
    bool IsBool() { return  type == TType::BOOLEAN; }
    bool IsNumeral() { return IsInteger() || IsDouble(); }
    bool IsInteger() { return type == TType::INTEGER; }
    bool IsString() { return  type == TType::STRING; }
    bool IsDouble() { return  type == TType::DOUBLE; } 
    bool IsNil() { return  type == TType::NIL; }
    /*TODO*/
    bool IsTrue() { return false;  }

    explicit Object(long i){
        type = TType::INTEGER;
        value =  new TValue(i);
    }

    explicit Object(double d){
        type = TType::DOUBLE;
        value =  new TValue(d);
    }

    Object(bool b){
        type = TType::BOOLEAN;
        value =  new TValue(b);
    }

    Object(char* s){
        type = TType::STRING;
        value =  new TValue(s);
    }

    Object(Object* o){
        type = TType::OBJECT;
        value =  new TValue(o);
    }

    const TValue* GetValue() { return value; }
    static Object* FromToken(Token* t);
    Object* operator+(Object rhs);
    Object* operator*(Object rhs);
    Object* operator-(Object rhs);
};


#endif
