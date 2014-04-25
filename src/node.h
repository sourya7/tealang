#ifndef T_NODE_H
#define T_NODE_H

class Node {
protected:
    Node* left;
    Node* right;
public:
    Node() {} 
    Node(Node* l, Node* r) : left(l), right(r) {} 
    void SetLeft(Node* l) { left = l; }
    void SetRight(Node* r) { right = r; }
};

#endif
