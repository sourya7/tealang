#include <algorithm>
#include "CodeObject.h"

using std::string;
using std::find;

int CodeObject::PushConst(SObject o) {
    consts->push_back(o);
    return consts->size() - 1;
}

int CodeObject::PushID(string var) {
    ids->push_back(var);
    vals->push_back(Object::NIL);
    assert(ids->size() == vals->size());
    return ids->size() - 1;
} 

//level returns if we can find it in a parent
int CodeObject::GetID(string var, int &level){
    bool found = false;
    level = 0;
    CodeObject* root = this;
    while(root != nullptr){
        auto it = find(root->ids->begin(), root->ids->end(), var);
        if(it != root->ids->end()) {
            return it - root->ids->begin();
        }
        level++;
        root = POINTER_VAL(root->parent);
    }
    //not found in any level
    level = -1;
    return -1;
}

void CodeObject::StoreIDVal(SObject val, int id, int level) { 
    CodeObject* root = this;
    while(level--){
        assert(root != nullptr);
        root = POINTER_VAL(root->parent);
    }
    assert(root->ids->size() > id); 
    root->vals->at(id) = val; 
}

int CodeObject::GetChildID(SCodeObj c){
    auto it = find(children->begin(), children->end(), c);
    if(it != children->end()) return it - children->begin();
    else return -1;
}

SObject CodeObject::GetIDVal(int id, int level){
    CodeObject* root = this;
    while(level--){
        assert(root != nullptr);
        root = POINTER_VAL(root->parent);
    }
    return root->vals->at(id); 
}

void CodeObject::AddChild(SCodeObj child) { 
    children->push_back(child); 
}

