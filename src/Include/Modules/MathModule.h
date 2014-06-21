#ifndef T_MATHMODULE_H
#define T_MATHMODULE_H

#include "Module.h"

#define BIND_METH_F(func, instance, size)                                      \
  make_pair(std::bind(&func, instance, _1), size)
#define BIND_INIT_F(func, size) make_pair(std::bind(&func, _1), size)

class MathModule;
typedef std::shared_ptr<MathModule> SMathModule;

using namespace std::placeholders;
class MathModule : public Module {
private:
public:
  MathModule();
  static SObject sqrt(const VecSObject &obj);
};

#endif
