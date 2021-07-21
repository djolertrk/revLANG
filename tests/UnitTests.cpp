// === This file implements UnitTesting for the CodeGen.

#include "CodeGen.h"

bool testBasicModuleCreationAndDeletion() {
  auto M = Module::create("m1.revLang");
  auto F = Function::create("f1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", F.get(), true);
  auto F1BB2 = BasicBlock::create("bb.1", F.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", F.get());

  F->removeBasicBlock(std::move(F1BB3));
  F->removeBasicBlock(std::move(F1BB2));
  F->removeBasicBlock(std::move(F1BB1));
  M->removeFunction(std::move(F));

  return true;
}

int main()
{
  if (!testBasicModuleCreationAndDeletion())
    return 1;

  return 0;
}
