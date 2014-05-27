#include "GC.h"
#include "Object.h"

class Module : public Object {
private:
  static map<string, SModule> _modules;
  string _moduleName;
  bool _loadDefault = false;
  ModuleFuncMap _funcMap;
  ModuleInitMap _initMap;
  bool _isInstance = false;

protected:

  Module(string moduleName)
      : Object(MakeShared<Value>(this, Type::MODULE)), _moduleName(moduleName) {}
  static SModule GetModuleFromObj(const SObject &obj) {
    return DYN_GC_CAST<Module>(obj);
  }
  void RegisterModule(const SModule& module, bool loadDefault) {
    _loadDefault = loadDefault;
    _modules[_moduleName] = module;
  }
  void SetInitMap(ModuleInitMap initMap) { _initMap = initMap; }
  void SetFuncMap(ModuleFuncMap funcMap) { _funcMap = funcMap; }
  void SetInstance() { _isInstance = true; }

public:
  int GetArgc(const SObject& method) const { return 0; }
  bool IsInstance() { return _isInstance; }
  static void LoadDefault(const SIRBuilder &builder);
    /*
   * LoadModule may load a module from the file or from the preloaded list of modules
   */
  static void LoadModule(const SObject &modulename);
  static SObject Call(const SObject &instance, const SObject &method,
                      const VecSObj &params);
};
