#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObj : public Object {
private:
  SCodeObj co;
  bool isInstance = false;

public:
  ClassObj(string cn, SCodeObj o)
      : Object(MakeShared<Value>(POINTER_VAL(o))), co(o) {
    SetName(cn);
    co->SetInstanceOf(WRAP_PTR<ClassObj>(this));
  }
  ClassObj(SCodeObj o) : Object(MakeShared<Value>(POINTER_VAL(o))) {
    isInstance = true;
    co = o;
    assert(co->GetInstanceOf() != nullptr);
  }
  bool IsInstance() const { return isInstance; }
};
#endif
