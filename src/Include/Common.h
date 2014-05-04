#ifndef T_COMMON_H
#define T_COMMON_H

typedef unsigned int uint;
typedef unsigned long ulong;
#include <sstream>

namespace COM{
    
    template <typename T> string toStr(T tmp)
    {
        ostringstream out;
        out << tmp;
        return out.str();
    }


    template <typename T> T strTo(string tmp)
    {
        T output;
        istringstream in(tmp);
        in >> output;
        return output;
    }
};

#endif
