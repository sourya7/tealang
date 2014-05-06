#ifndef T_GC_H
#define T_GC_H

#include <string>
#include <functional>
#include <map>
#include <stack>
#include <vector>

#ifdef ALLOW_GC
#include <gc/gc_cpp.h>
#include <gc/gc_allocator.h>
class TGC : public gc {
};

template<typename T>
struct GV{
        typedef std::vector<T,gc_allocator<T> > Vector;
};

template<typename K,typename V>
struct GM{
        typedef std::map<K, V, gc_allocator<std::pair<const K, V> > >  Map;
};

#else 
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
class Object;
class OP;
class CodeObject;
class FunctionObj;

using namespace std;

typedef GV<Object*>::Vector GCVecObjPtr;
typedef GV<string>::Vector GCVecString;
typedef GV<OP>::Vector GCVecOP;
typedef GV<CodeObject*>::Vector GCVecCodeObjPtr;
typedef GV<FunctionObj*>::Vector GCVecFuncObjPtr;
typedef pair<function<Object*(GCVecObjPtr)>, int> FuncSizePair;
typedef GM<string,FuncSizePair>::Map GCMapStrFunc;
typedef GV<Object*>::Vector GCStackObjPtr;


#endif
