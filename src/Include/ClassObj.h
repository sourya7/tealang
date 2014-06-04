#ifndef T_CLASSOBJ_H
#define T_CLASSOBJ_H
#include "Object.h"
#include "CodeObject.h"
class ClassObj : public Object {
private:
  SCodeObj _codeObj;
  bool _isInstance;

public:
  ClassObj(string cn, SCodeObj codeObj)
      : Object(MakeShared<Value>(Type::CLASS)), _codeObj(codeObj),
        _isInstance(false) {
    SetName(cn);
    //_codeObj->SetInstanceOf(WRAP_PTR<ClassObj>(this));
  }
  ClassObj(SCodeObj codeObj)
      : Object(MakeShared<Value>(this)), _codeObj(codeObj), _isInstance(true) {
    // assert(_codeObj->GetInstanceOf() != nullptr);
  }
  bool IsInstance() const { return _isInstance; }
  SCodeObj GetCodeObject() const { return MakeShared<CodeObject>(*_codeObj); }
};
#endif
