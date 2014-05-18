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
union Value;
class Lexer;

// }}}
// {{{ GC Class or Shared Pointers 
#ifdef ALLOW_GC
#include <gc/gc_cpp.h>
#include <gc/gc_allocator.h>
class TGC : public gc {
};

template<typename T>
struct GV{
    typedef std::vector<T,gc_allocator<T>> Vector;
};

template<typename K,typename V>
struct GM{
    typedef std::map<K,V,gc_allocator<std::pair<const K,V>>>  Map;
};
#else 
//Shared pointers
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
#endif

// }}}

typedef GV<OP>::Vector VecOP;
typedef GV<string>::Vector VecStr;

#ifdef ALLOW_GC
// {{{ Typedefs for GC vals
typedef int* SInt;
typedef VecOP* SVecOP;
typedef Object* SObject;
typedef CodeObject* SCodeObj;
typedef FunctionObj* SFunctionObj;
typedef VecStr* SVecStr;
typedef GV<SObject>::Vector VecSObj;
typedef GV<SCodeObj>::Vector VecSCodeObj;
typedef VecSCodeObj* SVecSCodeObj;
typedef VecSObj* SVecSObj;
typedef Token* SToken;
typedef NodeAST* SNodeAST;
typedef SeqAST* SSeqAST;
typedef IRBuilder* SIRBuilder;
typedef Parser* SParser;
typedef Value* SValue;
typedef Lexer* SLexer;
// }}}
#else
// {{{ Typedefs for shared pointers 
typedef shared_ptr<int> SInt;
typedef shared_ptr<VecOP> SVecOP;
typedef shared_ptr<Object> SObject;
typedef shared_ptr<CodeObject> SCodeObj;
typedef shared_ptr<FunctionObj> SFunctionObj;
typedef shared_ptr<VecStr> SVecStr;
typedef GV<SObject>::Vector VecSObj;
typedef GV<SCodeObj>::Vector VecSCodeObj;
typedef shared_ptr<VecSCodeObj> SVecSCodeObj;
typedef shared_ptr<VecSObj> SVecSObj;
typedef shared_ptr<Token> SToken;
typedef shared_ptr<NodeAST> SNodeAST;
typedef shared_ptr<SeqAST> SSeqAST;
typedef shared_ptr<IRBuilder> SIRBuilder;
typedef shared_ptr<Parser> SParser;
typedef shared_ptr<Value> SValue;
typedef shared_ptr<Lexer> SLexer;
// }}}
#endif
// {{{ Common to both GC and shared
typedef GV<SFunctionObj>::Vector VecSFuncObj;
typedef GV<SToken>::Vector VecSTok;
typedef GV<SNodeAST>::Vector VecSNodeAST;
typedef pair<function<SObject(const VecSObj&)>, int> FuncSizePair;
typedef map<string, FuncSizePair> MapStrFunc;
typedef GV<pair<SVecOP,SInt>>::Vector VecPairVecOPInt;
typedef GV<pair<OP,SInt>>::Vector VecPairOPSInt;
// }}} 

// {{{ GC/SharedPtr convinience functions/constants
#ifdef ALLOW_GC
#define POINTER_VAL(x) x
template <typename T, typename...Args>
inline T* MakeShared(Args &&...args) { return new T(std::forward<Args>(args)...); }

template <typename T, typename V>
inline T* DYN_GC_CAST(V val){ return dynamic_cast<T*>(val); }

template <typename T, typename V>
inline T* WRAP_PTR(V* v){ return v; }
#else
#define POINTER_VAL(x) x.get()
template <typename T, typename V>
inline shared_ptr<T> WrapPtr(V* v){ return shared_ptr<T>(v); }

template <typename T, typename... Args>
inline std::shared_ptr<T> MakeShared(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

template <typename T, typename V>
inline std::shared_ptr<T> DYN_GC_CAST(V val){ return dynamic_pointer_cast<T>(val); }
#endif
// }}}
#endif
