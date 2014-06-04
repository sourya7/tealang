#ifndef T_LISTMODULE_H
#define T_LISTMODULE_H

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

class ListModule;
typedef std::shared_ptr<ListModule> SListModule;

using namespace std::placeholders;
class ListModule : public Module {
private:
  std::vector<SObject> container_;

public:
  ListModule();
  static SObject init(const VecSObject &obj);
  SObject append(const VecSObject &obj);
  SObject count(const VecSObject &obj);
  SObject get(const VecSObject &obj);
  SObject reverse(const VecSObject &obj);
  SObject insert(const VecSObject &obj);
};

#endif
