#ifndef T_IOMODULE_H
#define T_IOMODULE_H

#include "GC.h"
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

class IOModule;
typedef shared_ptr<IOModule> SIOModule;

using namespace std::placeholders;
class IOModule : public Module {
public:
  IOModule();
  static SObject Println(const VecSObj &v);
  static SObject Print(const VecSObj &v);
  static SObject Printf(const VecSObj &v);
};

#endif
