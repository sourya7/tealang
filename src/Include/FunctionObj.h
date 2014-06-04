#ifndef T_FUNCTIONOBJ_H
#define T_FUNCTIONOBJ_H
#include "Object.h"
#include "CodeObject.h"
class FunctionObj : public Object {
private:
  int _argc;
  string _funcName;
  SCodeObj _codeObj;
  bool _init;

public:
  FunctionObj(string funcName, int argc, SCodeObj codeObj, bool init = false)
      : Object(MakeShared<Value>(Type::FUNCTION)), _argc(argc),
        _funcName(funcName), _codeObj(codeObj), _init(init) {}

  int GetArgc() const { return _argc; }
  bool IsInit() const { return _init; }
  string GetName() const { return _funcName; }

  SCodeObj GetCodeObject() const { return MakeShared<CodeObject>(*_codeObj); }
  SCodeObj GetCodeObject(const SCodeObj &codeObj) const {
    auto instance = GetCodeObject();
    instance->SetParent(codeObj);
    return instance;
  }
};
#endif
