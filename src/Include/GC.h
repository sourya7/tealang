#ifndef T_GC_H
#define T_GC_H

#include <string>
#include <functional>
#include <map>
#include <stack>
#include <vector>
#include <memory>

class TGC {
};

template<typename T>
struct GV{
        typedef std::vector<T> Vector;
};

template<typename K,typename V>
struct GM{
        typedef std::map<K, V>  Map;
};

class Token;
class NodeAST;
class Object;
class OP;
class CodeObject;
class FunctionObj;
class IRBuilder;
class SeqAST;

using namespace std;

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


typedef vector<SObject> VecSObj;
typedef vector<SCodeObj> VecSCodeObj;
typedef vector<SFunctionObj> VecSFuncObj;

typedef shared_ptr<VecSObj> SVecSObj;
typedef pair<function<SObject(const VecSObj&)>, int> FuncSizePair;
typedef map<string,FuncSizePair> MapStrFunc;
typedef vector<pair<SVecOP,SInt>> VecPairVecOPInt;

typedef vector<pair<OP,SInt>> VecPairOPSInt;

typedef shared_ptr<Token> SToken;
typedef vector<SToken> VecSTok;
typedef shared_ptr<NodeAST> SNodeAST;
typedef shared_ptr<SeqAST> SSeqAST;
typedef shared_ptr<IRBuilder> SIRBuilder;

#endif
