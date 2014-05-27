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

#define BIND_FUNC(func, instance) std::bind(&func, instance, _1)
#define BIND_INIT(func) std::bind(&func, _1)

class ListModule;
typedef shared_ptr<ListModule> SListModule;

using namespace std::placeholders;
class ListModule : public Module {
private:
  SModule instance;
  map<SObject, SObject> container;
  static SListModule List;
  ListModule(bool reg = false) : Module("List") {
    if (reg){
      RegisterModule(WRAP_PTR<ListModule>(new ListModule()), true);
    }
    ModuleInitMap initMap = { { "init", BIND_INIT(ListModule::Init) } };
    SetInitMap(initMap);
  }

public:
  static SObject Init(const VecSObj &obj);
  SObject Append(const VecSObj &obj);
  SObject Count(const VecSObj &obj);
  SObject Get(const VecSObj &obj);
  SObject Reverse(const VecSObj &obj);
  SObject Insert(const VecSObj &obj);
};

#endif
