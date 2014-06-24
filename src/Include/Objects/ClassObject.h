#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObject : public Object {
private:
  SCodeObject codeObject_;
  bool isInstance_;

public:
  ClassObject(std::string className, SCodeObject codeObject)
      : Object(std::make_shared<Value>(Type::CLASS)), codeObject_(codeObject),
        isInstance_(false) {
    setName(className);
    codeObject_->setBlockType(BlockType::CLASS);
  }
  ClassObject(SCodeObject codeObject)
      : Object(std::make_shared<Value>(Type::CLASS)), codeObject_(codeObject),
        isInstance_(true) {}
  bool isInstance() const { return isInstance_; }
  SCodeObject getCodeObject() const { return codeObject_; }
};
#endif
