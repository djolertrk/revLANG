// === This file implements UnitTesting for the CodeGen.

#include "CodeGen.h"

// This should be valid function.
bool testFunctionValidation1() {
  auto M = Module::create("m1.revLang");
  auto F = Function::create("f1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", F.get(), true);
  auto F1BB2 = BasicBlock::create("bb.1", F.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", F.get());
  F1BB2->addSuccessor("true", F1BB3.get());

  return F->isValid();
}

// This function shouldn't be valid (reason: unvisitted bb).
bool testFunctionValidation2() {
  auto M = Module::create("m1.revLang");
  auto F = Function::create("f1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", F.get(), true);
  auto F1BB2 = BasicBlock::create("bb.1", F.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", F.get());

  return F->isValid();
}

// This function shouldn't be valid (reason: no entry bb).
bool testFunctionValidation3() {
  auto M = Module::create("m1.revLang");
  auto F = Function::create("f1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", F.get());
  auto F1BB2 = BasicBlock::create("bb.1", F.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", F.get());

  return F->isValid();
}

bool testBasicModuleCreationAndDeletion() {
  auto M = Module::create("m2.revLang");
  auto GV1 = GlobalVariable::create(0, M.get());
  auto F = Function::create("f1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", F.get(), true);
  auto F1BB2 = BasicBlock::create("bb.1", F.get());
  OperandsTy LoadOps{GV1.get()};
  std::unique_ptr<Instruction> I1 =
      std::make_unique<Load>(LoadOps, F1BB2.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", F.get());

  F->removeBasicBlock(std::move(F1BB3));
  F1BB2->removeInstruction(std::move(I1));
  F->removeBasicBlock(std::move(F1BB2));
  F->removeBasicBlock(std::move(F1BB1));
  M->removeFunction(std::move(F));

  return true;
}

int main()
{
  if (!testBasicModuleCreationAndDeletion())
    return 1;

  // TODO: add a test for DOT file creation.

  if (!testFunctionValidation1())
    return 1;

  if (testFunctionValidation2())
    return 1;

  if (testFunctionValidation3())
    return 1;

  return 0;
}
