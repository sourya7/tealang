#ifndef T_GC_H
#define T_GC_H

#include <string>
#include <functional>
#include <map>
#include <stack>
#include <vector>
#include <memory>

using namespace std;

// {{{ Forward declarations for classes
class Token;
class NodeAST;
class Object;
class OP;
class CodeObject;
class FunctionObj;
class IRBuilder;
class SeqAST;
class Parser;
class Value;
class Lexer;
class Module;

// }}}
typedef vector<OP> VecOP;
typedef vector<string> VecStr;

typedef shared_ptr<int> SInt;
typedef shared_ptr<VecOP> SVecOP;
typedef shared_ptr<Object> SObject;
typedef shared_ptr<CodeObject> SCodeObj;
typedef shared_ptr<FunctionObj> SFunctionObj;
typedef shared_ptr<VecStr> SVecStr;
typedef vector<SObject> VecSObj;
typedef vector<SCodeObj> VecSCodeObj;
typedef shared_ptr<VecSCodeObj> SVecSCodeObj;
typedef shared_ptr<VecSObj> SVecSObj;
typedef shared_ptr<Token> SToken;
typedef shared_ptr<NodeAST> SNodeAST;
typedef shared_ptr<SeqAST> SSeqAST;
typedef shared_ptr<IRBuilder> SIRBuilder;
typedef shared_ptr<Parser> SParser;
typedef shared_ptr<Value> SValue;
typedef shared_ptr<Lexer> SLexer;
typedef shared_ptr<Module> SModule;

typedef vector<SFunctionObj> VecSFuncObj;
typedef vector<SToken> VecSTok;
typedef vector<SNodeAST> VecSNodeAST;
typedef pair<function<SObject(const VecSObj &)>, int> FuncSizePair;
typedef map<string, FuncSizePair> MapStrFunc;
typedef vector<pair<SVecOP, SInt> > VecPairVecOPInt;
typedef vector<pair<OP, SInt> > VecPairOPSInt;
typedef vector<SModule> VecMod;

typedef function<SObject(const VecSObj&)> ModuleFunc;
typedef function<SObject(const VecSObj&)> ModuleInit;

typedef map<string, ModuleInit> ModuleInitMap;
typedef map<string, ModuleFunc> ModuleFuncMap;

#define POINTER_VAL(x) x.get()
template <typename T, typename V> inline shared_ptr<T> WRAP_PTR(V *v) {
  return shared_ptr<T>(v);
}

template <typename T, typename... Args>
inline std::shared_ptr<T> MakeShared(Args &&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename V> inline std::shared_ptr<T> DYN_GC_CAST(V val) {
  return dynamic_pointer_cast<T>(val);
}

#endif
