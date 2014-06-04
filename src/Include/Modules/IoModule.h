#ifndef T_IOMODULE_H
#define T_IOMODULE_H

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

class IoModule;
typedef std::shared_ptr<IoModule> SIoModule;

using namespace std::placeholders;
class IoModule : public Module {
public:
  IoModule();
  static SObject println(const VecSObject &v);
  static SObject print(const VecSObject &v);
  static SObject printf(const VecSObject &v);
};

#endif
