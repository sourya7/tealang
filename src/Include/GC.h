#ifndef T_GC_H
#define T_GC_H

#include <string>
#include <functional>
#include <vector>
#include <map>

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
typedef  GM<string, pair<function<Object*(GCVecObjPtr)>, int>>::Map GCMapStrFunc;


#endif
