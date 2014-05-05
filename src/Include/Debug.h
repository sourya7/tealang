#ifndef T_DEBUG_H
#define T_DEBUG_H

#include <iostream>
using std::cerr;

#include <cassert>
#ifdef PRINTDEBUG
#define DEBUG(x) do { std::cerr << __FILE__ << ":" << __LINE__ << " " << x << std::endl; } while (0)
#else
#define DEBUG(x) 
#endif

template <typename T, typename V>
T GUARD_CAST(V val) {
    T tmp = dynamic_cast<T>(val);
    assert(tmp != 0);
    return tmp;
}
#endif
