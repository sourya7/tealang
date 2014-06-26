#ifndef T_INTEGERMODULE_H
#define T_INTEGERMODULE_H

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

class IntegerModule;
typedef std::shared_ptr<IntegerModule> SIntegerModule;

using namespace std::placeholders;
class IntegerModule : public Module {
public:
  IntegerModule();
  static SObject fromStr(const VecSObject &v);
  static SObject fromNum(const VecSObject &v);
};

#endif
