#ifndef T_GC_H
#define T_GC_H

#include <vector>
#include <map>

#if 0
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
#endif
