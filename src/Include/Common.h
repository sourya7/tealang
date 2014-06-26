#ifndef T_COMMON_H
#define T_COMMON_H

#include <sstream>
#include <string>
#include <functional>
#include <map>
#include <stack>
#include <vector>
#include <memory>

typedef unsigned int uint;
typedef unsigned long ulong;

namespace com {
template <typename T> std::string toStr(T tmp) {
  std::ostringstream out;
  out << tmp;
  return out.str();
}

template <typename T> T strTo(std::string tmp) {
  T output;
  std::istringstream in(tmp);
  in >> output;
  return output;
}

inline long fromStr(std::string num) {
  if (num[0] == '0') {
    if (num[1] == 'x') {
      return std::stol(num, 0, 16);
    } else if (isdigit(num[1])) {
      return std::stol(num, 0, 8);
    } else if (num[1] == 'b') {
      num = num.substr(2);
      return std::stol(num,0,2);
    }
  }
  return std::stol(num, 0, 10);
}
}

class Token;
class NodeAst;
class Object;
class Op;
class CodeObject;
class FunctionObject;
class IrBuilder;
class SeqAst;
class Parser;
class Value;
class Lexer;
class Module;

typedef std::vector<Op> VecOp;
typedef std::vector<std::string> VecString;

typedef std::shared_ptr<VecString> SVecString;
typedef std::shared_ptr<int> SInt;
typedef std::shared_ptr<VecOp> SVecOp;
typedef std::shared_ptr<Object> SObject;
typedef std::shared_ptr<CodeObject> SCodeObject;
typedef std::shared_ptr<FunctionObject> SFunctionObject;
typedef std::vector<SObject> VecSObject;
typedef std::vector<SCodeObject> VecSCodeObject;
typedef std::shared_ptr<VecSCodeObject> SVecSCodeObject;
typedef std::shared_ptr<VecSObject> SVecSObject;
typedef std::shared_ptr<Token> SToken;
typedef std::shared_ptr<NodeAst> SNodeAst;
typedef std::shared_ptr<SeqAst> SSeqAst;
typedef std::shared_ptr<IrBuilder> SIrBuilder;
typedef std::shared_ptr<Parser> SParser;
typedef std::shared_ptr<Value> SValue;
typedef std::shared_ptr<Lexer> SLexer;
typedef std::shared_ptr<Module> SModule;

typedef std::vector<SFunctionObject> VecSFunctionObject;
typedef std::vector<SToken> VecSToken;
typedef std::vector<SNodeAst> VecSNodeAst;
typedef std::pair<std::function<SObject(const VecSObject &)>, int>
PairFunctionSize;
typedef std::map<std::string, PairFunctionSize> MapStrFunc;
typedef std::vector<std::pair<SVecOp, SInt> > VecPairSVecOpSInt;
typedef std::vector<std::pair<Op, SInt> > VecPairOpSInt;
typedef std::vector<SModule> VecModule;

// template <typename T, typename V> inline std::shared_ptr<T> DYN_GC_CAST(V
// val) {
//  return dynamic_pointer_cast<T>(val);
//}

#endif
