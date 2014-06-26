#ifndef T_MODULE_H
#define T_MODULE_H

#include "Object.h"
typedef std::map<std::string, SModule> MapSModule;
typedef std::map<std::string, SObject> MapStrProp;

class Module : public Object {
private:
  static MapSModule modules_;
  std::string moduleName_;
  bool loadDefault_ = false;
  MapStrFunc funcMap_;
  MapStrFunc initMap_;
  MapStrProp propMap_;
  bool isInstance_ = false;

protected:
  Module(std::string moduleName)
      : Object(std::make_shared<Value>(Type::MODULE)), moduleName_(moduleName) {
  }
  static SModule getModuleFromObject(const SObject &object) {
    return std::dynamic_pointer_cast<Module>(object);
  }
  void setInitMap(MapStrFunc initMap) { initMap_ = initMap; }
  void setFuncMap(MapStrFunc funcMap) { funcMap_ = funcMap; }
  void setPropMap(MapStrProp propMap) { propMap_ = propMap; }
  void setInstance() { isInstance_ = true; }

public:
  static void init();
  int getArgc(const SObject &method) const;
  bool isInstance() { return isInstance_; }
  static void loadDefaults(const SIrBuilder &builder);
  static void addModule(std::string name, SModule module) {
    modules_[name] = module;
  }
  static bool isKnownModule(std::string moduleName);
  /*
 * LoadModule may load a module from the file or from the preloaded list of
 * modules
 */
  static void loadModule(std::string name, const SIrBuilder &builder);
  static SObject call(const SObject &instance, const SObject &method,
                      const VecSObject &params);
};

#endif
