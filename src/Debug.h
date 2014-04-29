#ifndef T_DEBUG_H
#define T_DEBUG_H

#include <iostream>
using std::cerr;

#include <cassert>
#define DEBUG(x) do { std::cerr << __FILE__ << ":" << __LINE__ << " " << x << std::endl; } while (0)


#endif
