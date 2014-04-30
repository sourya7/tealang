
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
};

class Object {
private:
    TType type = TType::NIL;
    TValue* value = nullptr;
    Object() { value = new TValue(); } 
public:
    static const Object NIL;
    bool IsBool() { return false; }
    bool IsInteger() { return false; }
    bool IsString() { return false; }
    bool IsDouble() { return false; } 
    bool IsNil() { return false; }
    bool IsTrue() { return false; }

    explicit Object(long i){
        type = TType::INTEGER;
        value->i = i;
    }

    explicit Object(double d){
        type = TType::DOUBLE;
        value->d = d;
    }

    Object(bool b){
        type = TType::BOOLEAN;
        value->b = b;
    }

    Object(char* s){
        type = TType::STRING;
        value->s = s;
    }

    Object(Object* o){
        type = TType::OBJECT;
        value->o = o;
    }

    static Object* FromToken(Token* t);
};

#endif
