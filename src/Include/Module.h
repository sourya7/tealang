#ifndef T_MODULE_H
#define T_MODULE_H

#include "GC.h"
#include "Object.h"

class Module : public Object {
private:
  static map<string, SModule> _modules;
  string _moduleName;
  bool _loadDefault = false;
  MapStrFunc _funcMap;
  MapStrFunc _initMap;
  bool _isInstance = false;

protected:
  Module(string moduleName)
      : Object(MakeShared<Value>(Type::MODULE)), _moduleName(moduleName) {}
  static SModule GetModuleFromObj(const SObject &obj) {
    return DYN_GC_CAST<Module>(obj);
  }
  void SetInitMap(MapStrFunc initMap) { _initMap = initMap; }
  void SetFuncMap(MapStrFunc funcMap) { _funcMap = funcMap; }
  void SetInstance() { _isInstance = true; }

public:
  static void Init();
  int GetArgc(const SObject &method) const;
  bool IsInstance() { return _isInstance; }
  static void LoadDefaults(const SIRBuilder &builder);
  static void AddModule(std::string name, Module *module) {
    _modules[name] = WRAP_PTR<Module>(module);
  }
  /*
 * LoadModule may load a module from the file or from the preloaded list of
 * modules
 */
  static void LoadModule(std::string name, const SIRBuilder &modulename);
  static SObject Call(const SObject &instance, const SObject &method,
                      const VecSObj &params);
};

#endif
