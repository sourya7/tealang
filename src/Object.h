
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
using std::string;

/*
 * 
 */

class TObject;
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
    TObject* o;
};

class TObject {
private:
    TType type = TType::NIL;
    TValue* value = nullptr;
    TObject() { value = new TValue(); } 
public:
    static const TObject NIL;
    bool IsBool() { return false; }
    bool IsInteger() { return false; }
    bool IsString() { return false; }
    bool IsDouble() { return false; } 
    bool IsNil() { return false; }
    bool IsTrue() { return false; }

    explicit TObject(long i){
        type = TType::INTEGER;
        value->i = i;
    }

    explicit TObject(double d){
        type = TType::DOUBLE;
        value->d = d;
    }

    TObject(bool b){
        type = TType::BOOLEAN;
        value->b = b;
    }

    TObject(char* s){
        type = TType::STRING;
        value->s = s;
    }

    TObject(TObject* o){
        type = TType::OBJECT;
        value->o = o;
    }

    static TObject* FromToken(Token* t);
};

#endif
