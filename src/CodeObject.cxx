#include <algorithm>
#include "CodeObject.h"

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
    cerr << "Storing ";
    if(val->IsFunction()) cerr << "<FUNCTION>";
    else cerr << val->GetValue()->l << " ";
    cerr << " into " << ids[id] << "\n";
    vals[id] = val; 
}

int CodeObject::GetChildID(CodeObject* c){
    auto it = find(children.begin(), children.end(), c);
    if(it != children.end()) return it - children.begin();
    else return -1;
}

void CodeObject::AddChild(CodeObject* child) { 
    children.push_back(child); 
}

