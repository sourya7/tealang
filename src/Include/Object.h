
#ifndef T_TYPE_H
#define T_TYPE_H
#include <string>
#include "Debug.h"
#include "Common.h"

enum class Type {
  INTEGER = 1,
  DOUBLE,
  BOOLEAN,
  STRING,
  FUNCTION,
  CLASS,
  MODULE,
  OBJECT,
  ITERATOR,
  NIL
};

class Value {
  SObject object_;
  std::string string_;
  bool bool_;
  double double_;
  long long_;
  Type type_;

public:
  Value() : type_(Type::NIL) {};
  Value(long value) : long_(value), type_(Type::INTEGER) {}
  Value(double value) : double_(value), type_(Type::DOUBLE) {}
  Value(bool value) : bool_(value), type_(Type::BOOLEAN) {}
  Value(std::string value) : string_(value), type_(Type::STRING) {}
  Value(Object *value) : type_(Type::OBJECT) {
    object_ = std::shared_ptr<Object>(value);
  }
  Value(Type type) : type_(type) {}

  long getInt() const { return long_; }
  double getDouble() const { return double_; }
  bool getBool() const { return bool_; }
  std::string getString() const { return string_; }
  SObject getObject() const { return object_; }
  Type getType() { return type_; }
};

class Object {
private:
  SValue value_;
  Object() { value_ = std::make_shared<Value>(); }

protected:
  std::string name_ = "OBJECT";
  Object(SValue value) { value_ = value; }
  void setName(std::string name) { name_ = name; }

public:
  static SObject NIL;
  static SObject fromToken(Token *);
  std::string getName() const { return name_; }
  virtual bool isTrue() const { return !isNil(); }
  virtual bool isBool() const { return false; }
  virtual bool isInteger() const { return false; }
  virtual bool isString() const { return false; }
  virtual bool isFunction() const { return false; }
  virtual bool isNumeral() const { return isInteger() || isDouble() || isBool(); }
  virtual bool isDouble() const { return value_->getType() == Type::DOUBLE; }
  virtual bool isNil() const { return value_->getType() == Type::NIL; }
  virtual bool isModule() const { return value_->getType() == Type::MODULE; }
  Type getType() const { return value_->getType(); }
  long getInt() const;
  double getDouble() const;
  bool getBool() const { return value_->getBool(); }
  std::string getString() const { return value_->getString(); }
  SObject getObject() const { return value_->getObject(); }
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
  virtual SObject operator==(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator%(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator!=(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator/(const SObject &rhs) {
    assert(false);
    return rhs;
  }
  virtual SObject operator&&(const SObject &rhs);
  virtual SObject operator||(const SObject &rhs);
  virtual std::string toString() const { return "<" + name_ + ">"; }
};

#endif
