#include "Modules/IoModule.h"
#include "Objects/StringObject.h"

IoModule::IoModule() : Module("IO") {
  auto testObj = std::make_shared<StringObject>("Hello world!");
  MapStrProp propMap = { { "TESTOBJ", testObj } };

  MapStrFunc funcMap = { { "print:", BIND_INIT_F(IoModule::print, 1) },
                         { "println:", BIND_INIT_F(IoModule::println, 1) },
                         { "printf:withF:",
                           BIND_INIT_F(IoModule::printf, 2) } };
  setInitMap(funcMap);
  setPropMap(propMap);
}

SObject IoModule::println(const VecSObject &v) {
  std::string s = v.back()->toString();
  std::cout << s << "\n";
  return nullptr;
}

SObject IoModule::print(const VecSObject &v) {
  std::string s = v.back()->toString();
  std::cout << s;
  return nullptr;
}

SObject IoModule::printf(const VecSObject &v) {
  std::string f = v[0]->toString();
  std::string s = v[1]->toString();
  std::cout << f << " " << s;
  return nullptr;
}
