#ifndef T_FUNCTIONOBJ_H
#define T_FUNCTIONOBJ_H
#include "Object.h"
#include "CodeObject.h"

class FunctionObject : public Object {
private:
  int argc_;
  std::string name_;
  SCodeObject codeObject_;
  bool isInit_;

public:
  FunctionObject(std::string name, int argc, SCodeObject codeObject,
                 bool init = false)
      : Object(std::make_shared<Value>(Type::FUNCTION)), argc_(argc),
        name_(name), codeObject_(codeObject), isInit_(init) {
    codeObject_->setBlockType(BlockType::FUNCTION);
  }

  int getArgc() const { return argc_; }
  bool isInit() const { return isInit_; }
  std::string getName() const { return name_; }

  SCodeObject getCodeObject() const {
    return std::make_shared<CodeObject>(*codeObject_);
  }
  SCodeObject getCodeObject(const SCodeObject &codeObject) const {
    auto instance = getCodeObject();
    instance->setParent(codeObject);
    return instance;
  }
};
#endif
