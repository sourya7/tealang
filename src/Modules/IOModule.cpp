#include "Modules/IOModule.h"

IOModule::IOModule() : Module("IO") {
  MapStrFunc funcMap = { { "print:", BIND_INIT_F(IOModule::Print, 1) },
                         { "println:", BIND_INIT_F(IOModule::Println, 1) },
                         { "printf:withF:",
                           BIND_INIT_F(IOModule::Printf, 2) } };
  SetInitMap(funcMap);
}

SObject IOModule::Println(const VecSObj &v) {
  string s = v.back()->ToString();
  cout << s << "\n";
  return nullptr;
}

SObject IOModule::Print(const VecSObj &v) {
  string s = v.back()->ToString();
  cout << s;
  return nullptr;
}

SObject IOModule::Printf(const VecSObj &v) {
  string f = v[0]->ToString();
  string s = v[1]->ToString();
  cout << f << " " << s;
  return nullptr;
}
