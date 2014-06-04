
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
#include "GC.h"
#include "Debug.h"
using std::string;
class Object;
class Token;
class FunctionObj;

/*
typedef unsigned int T_TYPE;
T_TYPE T_CTR = 1
#define NEW_TYPE(type) T_TYPE type =  T_CTR++;

NEW_TYPE(T_INTEGER)
NEW_TYPE(T_DOUBLE)
NEW_TYPE(T_BOOL)
NEW_TYPE(T_STRING)
NEW_TYPE(T_FUNCTION)
NEW_TYPE(T_OBJECT)
NEW_TYPE(T_NIL)
*/

enum class Type {
  INTEGER = 1,
  DOUBLE,
  BOOLEAN,
  STRING,
  FUNCTION,
  CLASS,
  MODULE,
  OBJECT,
  NIL
};

class Value {
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
  Value(Object *v) : type(Type::OBJECT) { o = WRAP_PTR<Object>(v); }
  Value(Type t) : type(t) {}

  int GetInt() const { return l; }
  int GetDouble() const { return d; }
  bool GetBool() const { return b; }
  string GetString() const { return s; }
  SObject GetObject() const { return o; }
  Type GetType() { return type; }
};

class Object {
private:
  SValue value;
  Object() { value = MakeShared<Value>(); }

protected:
  string name = "OBJECT";
  Object(SValue v) { value = v; }
  void SetName(string n) { name = n; }

public:
  static SObject NIL;
  static SObject FromToken(Token *);
  string GetName() { return name; }
  virtual bool IsTrue() const { return !IsNil(); }
  virtual bool IsBool() const { return false; }
  virtual bool IsInteger() const { return false; }
  virtual bool IsString() const { return false; }
  virtual bool IsFunction() const { return false; }
  virtual bool IsNumeral() const { return IsInteger() || IsDouble(); }
  virtual bool IsDouble() const { return value->GetType() == Type::DOUBLE; }
  virtual bool IsNil() const { return value->GetType() == Type::NIL; }
  Type GetType() { return value->GetType(); }
  int GetInt() const { return value->GetInt(); }
  int GetDouble() const { return value->GetDouble(); }
  bool GetBool() const { return value->GetBool(); }
  string GetString() const { return value->GetString(); }
  SObject GetObject() const { return value->GetObject(); }
  virtual SObject operator+(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator<(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator<=(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator>(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator>=(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator*(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator-(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator||(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator==(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator!=(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual string ToString() { return "<OBJECT>"; }
};

#endif
