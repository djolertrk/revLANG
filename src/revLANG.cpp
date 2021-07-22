// === This file contains an implementaion for the driver that will be used
// as an interpreter for the revLANG language.

#include "CodeGen.h"
#include <iostream>
#include <memory>

int main() {
  std::cout << "=== revLang interpreter ===\n";

  // Here we simulate/test adding of the language objects.
  // NOTE: Please find more cases in the tests/ directory.

  // NOTE: Please do note that the driver is the owner of the language
  // objects. It owns unique_ptrs<>, so it will be cleaned up
  // when the scope of the objects ends.
  // If you want to delete an object, please make sure you had
  // deleted its parent first!

  // Create the module.
  auto M = Module::create("my-module.revLang");
  auto Func1 = Function::create("fn1", M.get());
  auto F1BB1 = BasicBlock::create("bb.0", Func1.get(), true);
  auto F1BB2 = BasicBlock::create("bb.1", Func1.get());
  F1BB1->addSuccessor("true", F1BB2.get());
  auto F1BB3 = BasicBlock::create("bb.2", Func1.get());
  F1BB2->addSuccessor("false", F1BB3.get());

  auto Func2 = Function::create("fn2", M.get());
  auto F2BB1 = BasicBlock::create("bb.0", Func2.get(), true);
  auto F2BB2 = BasicBlock::create("bb.1", Func2.get());
  auto F2BB3 = BasicBlock::create("bb.2", Func2.get());

  auto Func3 = Function::create("fn3", M.get());
  auto F3BB1 = BasicBlock::create("bb.0", Func3.get(), true);
  auto F3BB2 = BasicBlock::create("bb.1", Func3.get());
  auto F3BB3 = BasicBlock::create("bb.2", Func3.get());

  // An empty function.
  auto Func4 = Function::create("fn4", M.get());
  // Print the module.
  std::cout << "*** Module before the optimizations ***\n";
  M->dump();

  // This is an empty function, lets delete it.
  M->removeFunction(std::move(Func4));

  // Delete the bb.
  Func3->removeBasicBlock(std::move(F3BB3));

  // Print the module again.
  std::cout << "*** Module after the optimizations ***\n";
  M->dump();

  // Create a function that will be used for the DOT.
  auto Func5 = Function::create("foo", M.get());
  auto F5BB1 = BasicBlock::create("entry", Func5.get(), true);
  auto F5BB2 = BasicBlock::create("H", Func5.get());
  F5BB1->addSuccessor("true", F5BB2.get());
  auto F5BB3 = BasicBlock::create("I", Func5.get());
  F5BB1->addSuccessor("false", F5BB3.get());
  auto F5BB4 = BasicBlock::create("J", Func5.get());
  F5BB2->addSuccessor("", F5BB4.get());
  F5BB3->addSuccessor("", F5BB4.get());

  // Print the function in terms of DOT.
  Func5->printCFGAsDOT("revLang-cfg.dot");

  return 0;
}
