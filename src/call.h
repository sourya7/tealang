#ifndef T_CALL_H
#define T_CALL_H

#include "node.h"

class Call : public Node {
private:
    Node* param;
    Node* object;
public:
    void SetParam(Node* p) { param = p; }
    void SetObj(Node* o) { object = o; }

};
#endif
