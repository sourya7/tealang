#define BIND_INIT_F(func,argc) std::bind(&func,argc)

SObject IOModule::IOModule() : Module("IO") {
  MapStrFunc funcMap = {
    { "print:", BIND_INIT_F(&IOModule::Print, 1) },
    { "println:", BIND_INIT_F(&IOModule::Println, 1) },
    { "printf:withF:", BIND_INIT_F(&IOModule::Printf, 2) };
  SetInitMap(funcMap);
}

SObject Println(const VecSObj &v) {
  string s = v.back()->ToString();
  cout << s << "\n";
  return nullptr;
}

SObject Print(const VecSObj &v) {
  string s = v.back()->ToString();
  cout << s;
  return nullptr;
}

SObject Printf(const VecSObj &v) {
  string f = v[0]->ToString();
  string s = v[1]->ToString();
  cout << f << " " << s;
  return nullptr;
}
