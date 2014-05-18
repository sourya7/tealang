
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
#include "GC.h"
#include "Debug.h"
#include "CodeObject.h"
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
    CODE,
    NIL
};

/*
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
*/

class Value {
    SCodeObj co;
    SObject o;
    string s;
    bool b;
    double d;
    long l;
    Type type;
public:
    Value() : type(Type::NIL) {};
    Value(long v) : l(v), type(Type::INTEGER) {}
    Value(double v) : d(v), type(Type::DOUBLE) {}
    Value(bool v) : b(v), type(Type::BOOLEAN) {}
    Value(string v) : s(v), type(Type::STRING) {}
    Value(Object* v) : type(Type::OBJECT) { o = WRAP_PTR<Object>(v); }
    Value(CodeObject* v) : type(Type::CODE) { co = WRAP_PTR<CodeObject>(v); }

    int GetInt() const { return l; }
    int GetDouble() const { return d; }
    bool GetBool() const { return b; }
    string GetString() const { return s; }
    SCodeObj GetCodeObject() const { return co; }
    SObject GetObject() const { return o; }

    Type GetType() { return type; }
};

class Object : public TGC {
private:
    SValue value;
    Object() { value = MakeShared<Value>(); }
protected:
    string name = "OBJECT";
    Object(SValue v)  { value = v; }
    void SetName(string n) { name = n; }
public:
    static SObject NIL;
    static SObject FromToken(Token*);
    string GetName() { return name; }
    virtual bool IsTrue() const { return !IsNil(); }
    virtual bool IsBool() const { return false; }
    virtual bool IsInteger() const { return false; }
    virtual bool IsString() const { return false; }
    virtual bool IsFunction() const { return false; }
    virtual bool IsNumeral() const { return IsInteger() || IsDouble(); }
    virtual bool IsDouble() const { return value->GetType() == Type::DOUBLE; } 
    virtual bool IsNil() const { return value->GetType() == Type::NIL; }
    int GetInt() const { return value->GetInt(); }
    int GetDouble() const { return value->GetDouble(); }
    bool GetBool() const { return value->GetBool(); }
    string GetString() const { return value->GetString(); } 

    SCodeObj GetCodeObject() const { return value->GetCodeObject(); }
    SObject GetObject() const { return value->GetObject(); }

    virtual SObject operator+(SObject rhs) {assert(false); return nullptr; }
    virtual SObject operator*(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator-(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator==(SObject rhs) {assert(false); return nullptr;}
    virtual SObject operator!=(SObject rhs) {assert(false); return nullptr; }
    virtual string ToString() { return "<OBJECT>"; }
};


#endif  
