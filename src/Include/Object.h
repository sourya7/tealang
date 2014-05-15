
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

enum class Type {
    INTEGER = 1,
    DOUBLE,
    BOOLEAN,
    STRING,
    FUNCTION,
    OBJECT,
    CLASS,
    NIL
};

union Value {
    long l;
    double d;
    bool b;
    const char* s;
    Object* o;
    CodeObject* co;

    Value(long v) : l(v) {}
    Value(double v) : d(v) {}
    Value(bool v) : b(v) {}
    Value(const char* v) : s(v) {}
    Value(Object* v) : o(v) {}
    Value(CodeObject* v) : co(v) {}
};

class Object : public TGC {
private:
    Type type;
    Object() : Object(Type::NIL, nullptr) {}; 
protected:
    SValue value;
    Object(Type t, SValue v) : type(t) { 
        value = v;
    }
    Object(Type t) : type(t) { }
public:
    static SObject NIL;
    static SObject FromToken(Token*);
    virtual bool IsTrue() const { return !IsNil(); }
    virtual bool IsBool() const { return false; }
    virtual bool IsInteger() const { return false; }
    virtual bool IsString() const { return false; }
    virtual bool IsFunction() const { return false; }
    virtual bool IsNumeral() const { return IsInteger() || IsDouble(); }
    virtual bool IsDouble() const { return  type == Type::DOUBLE; } 
    virtual bool IsNil() const { return  type == Type::NIL; }
    int GetInt() { return value->l; }
    int GetDouble() { return value->d; }
    bool GetBool() { return value->b; }
    const char* GetString() { return value->s; }
    CodeObject* GetCodeObject() { return value->co; }
    Object* GetObject() { return value->o; }

    virtual SObject operator+(SObject rhs) {assert(false); return nullptr; }
    virtual SObject operator*(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator-(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator==(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator!=(SObject rhs) {assert(false); return nullptr; }
    virtual string ToString() { return "<OBJECT>"; }
    SValue GetValue() const { return value; } 
};


#endif  
