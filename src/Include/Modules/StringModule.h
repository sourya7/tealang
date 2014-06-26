#ifndef T_STRMODULE_H
#define T_STRMODULE_H

#include "Module.h"

/*
 * var a = [List init]
 * [a append: 2]
 *
 * if(instance->IsCModule()){
 *  Module::CallMethod(instance, funcName);
 * }
 */

#define BIND_METH_F(func, instance, size)                                      \
  make_pair(std::bind(&func, instance, _1), size)
#define BIND_INIT_F(func, size) make_pair(std::bind(&func, _1), size)

class StringModule;
typedef std::shared_ptr<StringModule> SStringModule;

using namespace std::placeholders;
class StringModule : public Module {
public:
  StringModule();
  static SObject fromObj(const VecSObject &v);
  static SObject length(const VecSObject &v);
  static SObject find(const VecSObject &v);
};

#endif
