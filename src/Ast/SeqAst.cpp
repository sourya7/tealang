#include "Ast/SeqAst.h"

SSeqAst SeqAst::addSeq(SNodeAst n) {
  left_ = n;
  auto rs = std::make_shared<SeqAst>(this);
  right_ = rs;
  return rs;
}

void SeqAst::generateIr(SIrBuilder builder) {
  if (left_.get() != nullptr)
    left_->generateIr(builder);
  if (right_.get() != nullptr)
    right_->generateIr(builder);
}
