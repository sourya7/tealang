#ifndef T_FUNCTIONOBJ_H
#define T_FUNCTIONOBJ_H
#include "Object.h"
#include "CodeObject.h"
class FunctionObj : public Object {
private:
  int _argc;
  string _funcName;
  SCodeObj _codeObj;
  bool _isC;

public:
  FunctionObj(string funcName, int argc, SCodeObj codeObj)
      : Object(MakeShared<Value>(this)), _argc(argc), _funcName(funcName),
        _codeObj(codeObj), _isC(false) {}
  FunctionObj(string funcName, int argc)
      : Object(MakeShared<Value>(this)), _argc(argc), _funcName(funcName),
        _codeObj(nullptr), _isC(true) {}

  int GetArgc() const { return _argc; }
  bool IsCFunction() const { return _isC; }
  string GetName() const { return _funcName; }

  SCodeObj GetCodeObject() const { return MakeShared<CodeObject>(*_codeObj); }
  SCodeObj GetCodeObject(const SCodeObj &codeObj) const {
    auto instance = GetCodeObject();
    instance->SetParent(codeObj);
    return instance;
  }
};
#endif
