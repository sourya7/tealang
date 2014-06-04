#include "ObjOP.h"
#include "StringObj.h"
namespace ObjOP {
SObject Add(SObject a, SObject b) {
  SObject ob = *a + b;
  return ob;
}
SObject Sub(SObject a, SObject b) {
  SObject ob = *a - b;
  return ob;
}
SObject Mul(SObject a, SObject b) {
  SObject ob = *a * b;
  return ob;
}
SObject Equal(SObject a, SObject b) {
  SObject ob = *a == b;
  return ob;
}
}
