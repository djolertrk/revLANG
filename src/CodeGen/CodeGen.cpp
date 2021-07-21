// === This contains the implementation of the revLANG IR constructs.

#include "CodeGen.h"

#include <cassert>
#include <iostream>

//
// Implementation of the BasicBlock class.
//

BasicBlock::BasicBlock(std::string basicBlockID, Function *parent)
    : BasicBlockID(basicBlockID), Parent(parent) {}

void BasicBlock::dump() const {
  std::cout << ' ' << BasicBlockID << ":\n";
}

// Could be used if we are changing the function (e.g. attributes,
// or we are inlining the block).
void BasicBlock::setParent(Function *parent) { Parent = parent; }
Function *BasicBlock::getParent() const { return Parent; }

std::unique_ptr<BasicBlock> BasicBlock::create(std::string basicBlockID,
                                               Function *parent,
                                               bool isEntryBasicBlock) {
  auto BB = std::make_unique<BasicBlock>(basicBlockID, parent);
  if (isEntryBasicBlock)
    parent->setEntryBB(BB.get());
  parent->addBasicBlock(basicBlockID, BB.get());
  return BB;
}

const std::string& BasicBlock::getBBID() const { return BasicBlockID; }

void BasicBlock::remove() {
  // TODO: implement this when the instructions are implemented.
}

//
// Implementation of the Function.
//

Function::Function(std::string functionID, Module *parent)
    : FunctionID(functionID), Parent(parent) {}

void Function::dump() const {
  std::cout << "def " << FunctionID << "():\n";

  // If the function is empty, it should be deleted.
  if (empty()) {
    std::cout << "  empty function\n\n";
    return;
  }

  auto BBs = getBasicBlocks();
  // Print all the bbs.
  for (const auto &BB : BBs)
    BB.second->dump();

  // NOTE: Use '\n', since it is faster than "\n".
  std::cout << '\n';
}

bool Function::empty() const {
  return getNumberOfBBs() == 0;
}

// Could be used if we are changing the module, e.g. LTO.
void Function::setParent(Module *parent) { Parent = parent; }
Module *Function::getParent() const { return Parent; }

void Function::setEntryBB(BasicBlock *bb) { EntryBB = bb; }
BasicBlock *Function::getEntryBB() const { return EntryBB; }

void Function::addBasicBlock(const std::string &bbName, BasicBlock *bb) {
  assert(!BasicBlocks.count(bbName) && "The basic block already exists");
  BasicBlocks[bbName] = bb;
}
BasicBlockList &Function::getBasicBlocks() const {
  // According to the type deduction rules when dealing with templates,
  // the reference drops const qualifier, so we need explicit casting
  // here.
  return const_cast<BasicBlockList &>(BasicBlocks);
}

std::unique_ptr<Function> Function::create(std::string functionID,
                                           Module *parent) {
  auto F = std::make_unique<Function>(functionID, parent);
  parent->addFunction(functionID, F.get());
  return F;
}

size_t Function::getNumberOfBBs() const { return BasicBlocks.size(); }

const std::string& Function::getFnID() const { return FunctionID; }

void Function::removeBasicBlock(std::unique_ptr<BasicBlock> bb) {
  //assert(bb->empty() && "Delete the instructions first");
  auto bbName = bb->getBBID();
  BasicBlocks.erase(bbName);
}

//
// Implementation of the Module class.
//

Module::Module(std::string moduleID) : ModuleID(moduleID) {}

void Module::dump() const {
  std::cout << "ModuleID: " << ModuleID << "\n\n";

  // Print functions.
  auto Fns = getFunctions();
  for (const auto &F : Fns)
    F.second->dump();
}

void Module::addFunction(const std::string &fnName, Function *f) {
  assert(!Functions.count(fnName) && "The function already exists");
  Functions[fnName] = f;
}

FunctionList &Module::getFunctions() const {
  // According to the type deduction rules when dealing with templates,
  // the reference drops const qualifier, so we need explicit casting
  // here.
  return const_cast<FunctionList &>(Functions);
}

size_t Module::getNumberOfFns() const { return Functions.size(); }

void Module::removeFunction(std::unique_ptr<Function> f) {
  assert(f->empty() && "Delete the basic blocks first");
  auto fnName = f->getFnID();
  Functions.erase(fnName);
}
