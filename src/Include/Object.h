
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
#include "GC.h"
#include "Debug.h"
using std::string;

/*
 * 
 */

class Object;
class Token;
class CodeObject;
class FunctionObj;

enum class TType {
    INTEGER = 1,
    DOUBLE,
    BOOLEAN,
    STRING,
    FUNCTION,
    OBJECT,
    NIL
};

union TValue {
    long l;
    double d;
    bool b;
    const char* s;
    Object* o;
    CodeObject* co;

    TValue(long v) : l(v) {}
    TValue(double v) : d(v) {}
    TValue(bool v) : b(v) {}
    TValue(const char* v) : s(v) {}
    TValue(Object* v) : o(v) {}
    TValue(CodeObject* v) : co(v) {}
};

class Object : public TGC {
private:
    TType type;
    Object() : Object(TType::NIL, nullptr) {}; 
protected:
    TValue* value = nullptr;
    Object(TType t, TValue* v) : type(t), value(v) { }
    Object(TType t) : type(t) { }
public:
    static Object* NIL;
    static Object* FromToken(Token*);
    virtual bool IsTrue() { return !IsNil(); }
    virtual bool IsBool() { return false; }
    virtual bool IsInteger() { return false; }
    virtual bool IsString() { return false; }
    virtual bool IsFunction() { return false; }
    virtual bool IsNumeral() { return IsInteger() || IsDouble(); }
    virtual bool IsDouble() { return  type == TType::DOUBLE; } 
    virtual bool IsNil() { return  type == TType::NIL; }
    int GetInt() { return value->l; }
    int GetDouble() { return value->d; }
    bool GetBool() { return value->b; }
    const char* GetString() { return value->s; }
    CodeObject* GetCodeObject() { return value->co; }
    Object* GetObject() { return value->o; }

    virtual Object* operator+(Object* rhs) {}
    virtual Object* operator*(Object* rhs) {}
    virtual Object* operator-(Object* rhs) {}
    virtual string ToString() { return "<OBJECT>"; }
    TValue* GetValue() { return value; } 
};


#endif  
