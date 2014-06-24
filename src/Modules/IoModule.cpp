#include "Modules/IoModule.h"

IoModule::IoModule() : Module("IO") {
  MapStrFunc funcMap = { { "print:", BIND_INIT_F(IoModule::print, 1) },
                         { "println:", BIND_INIT_F(IoModule::println, 1) },
                         { "printf:withF:",
                           BIND_INIT_F(IoModule::printf, 2) } };
  setInitMap(funcMap);
}

SObject IoModule::println(const VecSObject &v) {
  std::string s = v.back()->toString();
  std::cerr << s << "\n";
  return nullptr;
}

SObject IoModule::print(const VecSObject &v) {
  std::string s = v.back()->toString();
  std::cerr << s;
  return nullptr;
}

SObject IoModule::printf(const VecSObject &v) {
  std::string f = v[0]->toString();
  std::string s = v[1]->toString();
  std::cerr << f << " " << s;
  return nullptr;
}
