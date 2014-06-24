#ifndef T_IMPORTAST_H
#define T_IMPORTAST_H

#include "NodeAst.h"

class ImportAst : public NodeAst {
private:
  std::string moduleName_;

public:
  ImportAst(std::string moduleName, SNodeAst root)
      : NodeAst(NodeType::IMPORT, root, nullptr), moduleName_(moduleName) {}
  void generateIr(SIrBuilder builder);
};

#endif
