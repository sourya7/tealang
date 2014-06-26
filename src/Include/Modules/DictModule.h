#ifndef T_DICTMODULE_H
#define T_DICTMODULE_H

#include "Module.h"

/*
 * var a = [Dict init]
 * [a append:2 withKey:"Some"]
 *
 * if(instance->IsCModule()){
 *  Module::CallMethod(instance, funcName);
 * }
 */

#define BIND_METH_F(func, instance, size)                                      \
  make_pair(std::bind(&func, instance, _1), size)
#define BIND_INIT_F(func, size) make_pair(std::bind(&func, _1), size)

class DictModule;
typedef std::shared_ptr<DictModule> SDictModule;

struct SObjMapCmp {
  bool operator()(const SObject &a, const SObject &b) const {
    return !((*a == b)->isTrue());
  }
};

using namespace std::placeholders;
class DictModule : public Module {
private:
  std::map<SObject,SObject,SObjMapCmp> container_;

public:
  DictModule();
  static SObject init(const VecSObject &obj);
  static SObject initInternal();
  SObject append(const VecSObject &obj);
  SObject count(const VecSObject &obj);
  SObject get(const VecSObject &obj);
  SObject insert(const VecSObject &obj);
};

#endif
