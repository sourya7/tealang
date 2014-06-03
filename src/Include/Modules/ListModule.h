#ifndef T_LISTMODULE_H
#define T_LISTMODULE_H

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

class ListModule;
typedef shared_ptr<ListModule> SListModule;

using namespace std::placeholders;
class ListModule : public Module {
private:
  SModule instance;
  vector<SObject> container;

public:
  ListModule();
  static SObject Init(const VecSObj &obj);
  SObject Append(const VecSObj &obj);
  SObject Count(const VecSObj &obj);
  SObject Get(const VecSObj &obj);
  SObject Reverse(const VecSObj &obj);
  SObject Insert(const VecSObj &obj);
};

#endif
