#include <algorithm>
#include "CodeObject.h"

using std::vector;
using std::string;
using std::find;

int CodeObject::PushConst(Object* o) {
    consts.push_back(o);
    return consts.size() - 1;
}

int CodeObject::PushID(string var) {
    ids.push_back(var);
    vals.push_back(Object::NIL);
    assert(ids.size() == vals.size());
    return ids.size() - 1;
} 

int CodeObject::GetID(string var){
    auto it = find(ids.begin(), ids.end(), var);
    if(it != ids.end()) return it - ids.begin();
    else return -1;
}

void CodeObject::StoreIDVal(int id, Object* val) { 
    assert(ids.size() > id); 
    vals[id] = val; 
}

