#ifndef T_NODE_H
#define T_NODE_H

enum class NodeType {NODE, SEQ, CALL, PARAM, IFSTMT, FSTMT, ASSIGN, EXPR};
class Node {
protected:
    Node* left;
    Node* right;
    NodeType type = NodeType::NODE;
public:
    Node() {} 
    Node(NodeType t) : type(t) {} 
    Node(Node* l, Node* r) : left(l), right(r) {} 
    Node(NodeType t, Node *l, Node* r) : type(t), left(l), right(r) {} 
    void SetLeft(Node* l) { left = l; }
    void SetRight(Node* r) { right = r; }
};

#endif
