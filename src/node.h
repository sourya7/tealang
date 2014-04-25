#ifndef T_NODE_H
#define T_NODE_H

#include <string>
#include <iostream>
using std::string;
using std::cerr;

enum class NodeType {NODE, SEQ, CALL, PARAM, IFSTMT, FSTMT, ASSIGN, EXPR, TOKEN};
class Node {
protected:
    Node* left = nullptr;
    Node* right = nullptr; 
    NodeType type = NodeType::NODE;
public:
    Node() {}
    Node(NodeType t) : type(t) {} 
    Node(Node* l, Node* r) : left(l), right(r) {} 
    Node(NodeType t, Node *l, Node* r) : type(t), left(l), right(r) {} 
    void SetLeft(Node* l) { left = l; }
    void SetRight(Node* r) { right = r; }
    virtual void Display(int level=0) {
        cerr << string(level*2, ' ');
        switch(type){
            case NodeType::NODE: cerr << "NODE"; break;
            case NodeType::SEQ: cerr << "SEQ"; break;
            case NodeType::CALL: cerr << "CALL"; break;
            case NodeType::PARAM: cerr << "PARAM"; break;
            case NodeType::IFSTMT: cerr << "IFSTMT"; break;
            case NodeType::FSTMT: cerr << "FSTMT"; break;
            case NodeType::ASSIGN: cerr << "ASSIGN"; break;
            case NodeType::EXPR: cerr << "EXPR"; break;
            case NodeType::TOKEN: cerr << "TOKEN"; break;
        }
        cerr << "\n";
        if(left != nullptr) left->Display(level+1);
        if(right != nullptr) right->Display(level+1);
    }
};

#endif
