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

//level returns if we can find it in a parent
int CodeObject::GetID(string var, int &level){
    bool found = false;
    level = 0;
    CodeObject* root = this;
    while(root != nullptr){
        auto it = find(root->ids.begin(), root->ids.end(), var);
        if(it != root->ids.end()) {
            return it - root->ids.begin();
        }
        level++;
        root = root->parent;
    }
    //not found in any level
    level = -1;
    return -1;
}

void CodeObject::StoreIDVal(Object* val, int id, int level) { 
    CodeObject* root = this;
    while(level--){
        assert(root != nullptr);
        root = root->parent;
    }
    assert(root->ids.size() > id); 
    cerr << "Storing ";
    if(val->IsFunction()) cerr << "<FUNCTION>";
    else cerr << val->GetValue()->l << " ";
    cerr << " into " << root->ids[id] << "\n";
    root->vals[id] = val; 
}

int CodeObject::GetChildID(CodeObject* c){
    auto it = find(children.begin(), children.end(), c);
    if(it != children.end()) return it - children.begin();
    else return -1;
}

Object* CodeObject::GetIDVal(int id, int level){
    CodeObject* root = this;
    while(level--){
        assert(root != nullptr);
        root = root->parent;
    }
    return root->vals[id]; 
}

void CodeObject::AddChild(CodeObject* child) { 
    children.push_back(child); 
}

