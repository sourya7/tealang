#ifndef T_SocketModule_H
#define T_SocketModule_H

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

class SocketModule;
typedef std::shared_ptr<SocketModule> SSocketModule;

using namespace std::placeholders;
class SocketModule : public Module {
private:
  int socket_ = -1;
  int accept_ = -1;
  int domain_;
  int type_;
  int proto_;
public:
  SocketModule();
  static SObject init(const VecSObject &obj);
  SObject bind(const VecSObject &obj);
  SObject listen(const VecSObject &obj);
  SObject accept(const VecSObject &obj);
  SObject recv(const VecSObject &obj);
  SObject send(const VecSObject &obj);
  SObject close(const VecSObject &obj);
};

#endif
