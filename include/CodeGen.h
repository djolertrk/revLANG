//=== Classes to represent a module; functions; basic blocks; instructions.

#include <memory>
#include <string>
#include <map>
#include <vector>

class BasicBlock;
class GlobalVariable;
class Function;
class Module;
class Instruction;

// Symbol tables for representing the named language items.
// Since we are going to iterate through the items, we are using
// the map. We can use std::unordered_map<> (hash_map) for checking if the
// named item is already there and for iteration the std::map<> (which
// is a red-black-tree), since it keeps the order. But, for
// the purpose of this exercise I pay the O(logN) price, and I'll use
// the std::map<> only.

// This key represents the fn name and the value is the Function pointer.
using FunctionList = std::map<std::string, Function *>;
// This key represents the bb name and the value is the BasicBlock pointer.
using BasicBlockList = std::map<std::string, BasicBlock *>;
// This key represents the tag and the value is the BasicBlock pointer.
using SuccessorBBList = std::map<std::string, BasicBlock *>;
// This key represents the var id and the value is the GlobalVariable pointer.
using GlobalVarList = std::map<unsigned, GlobalVariable *>;

// This represents the type for list of instructions.
using InstrustionList = std::vector<Instruction *>;
// This represents the type for list of operands.
using OperandsTy = std::vector<GlobalVariable *>;

// This represents global variables.
class GlobalVariable {
  Module *Parent;
  unsigned ID;
public:
  GlobalVariable(unsigned id, Module *parent);

  // Creates a new GlobalVariable.
  static std::unique_ptr<GlobalVariable> create(unsigned id, Module *parent);

  void setParent(Module *parent);
  Module *getParent() const;
  unsigned getID() const { return ID; }

  // Prints the var to stdout.
  void dump() const;
};

// This represents an Instruction.
class Instruction {
protected:
  OperandsTy Ops;
  std::string OpCode;
  BasicBlock *Parent;
public:
  virtual ~Instruction() {}
  OperandsTy& getOps() const { return const_cast<OperandsTy&>(Ops); }
  const std::string& getOpCode() const { return OpCode; }
  virtual void dump() const = 0;
};

// This represents a LOAD instruciton.
// It has a single operand representing the load address.
class Load : public Instruction {
public:
  Load (OperandsTy& ops, BasicBlock *parent);
  void dump() const override;
};

// This represents a STORE instruciton.
// It has two arguments; the first is the value to store in memory,
// and the second is the address.
class Store : public Instruction {
public:
  Store (OperandsTy& ops, BasicBlock *parent);
  void dump() const override;
};

// This represents an ADD instruciton.
// It has 3 or more operands.
class Add : public Instruction {
public:
  Add (OperandsTy& ops, BasicBlock *parent);
  void dump() const override;
};

// This represents a basic block on the revLANG IR level.
class BasicBlock {
  InstrustionList Instructions;
  SuccessorBBList Successors;
  std::string BasicBlockID;
  Function *Parent;

  void setParent(Function *parent);
  Function *getParent() const;

 public:
  // A name for the function must be provided when doing the construction.
  // The creation should be handled via the factory method.
  BasicBlock(std::string basicBlockID, Function *parent);
  // Prints the BB to stdout.
  void dump() const;

  // Creates a new BasicBlock.
  static std::unique_ptr<BasicBlock> create(std::string basicBlockID, Function *parent,
                            bool isEntryBasicBlock = false);

  const std::string& getBBID() const;

  // This should do all the cleanups.
  void removeInstruction(std::unique_ptr<Instruction> instr);

  void removeSuccessor(BasicBlock *bb);

  // Add successor bb.
  void addSuccessor(const std::string &tag, BasicBlock *bb);
  SuccessorBBList& getSuccessors() const;
  size_t getNumOfSuccessors() const;

  // Add the instruction.
  void addInstruction(Instruction *inst);
  InstrustionList& getInstructions() const;

  size_t getNumOfInstrs() const;
};

// This represents a function on the revLANG IR level. A function contains one
// or more basic blocks. One of them is the entry basic block.
class Function {
  BasicBlockList BasicBlocks;
  std::string FunctionID;
  Module *Parent;
  BasicBlock *EntryBB = nullptr;

  void setParent(Module *parent);
  Module *getParent() const;

 public:
  // A name for the function must be provided when doing the construction.
  Function(std::string functionID, Module *parent);
  // Prints the function to stdout.
  void dump() const;

  // This should be called from Function::Create().
  void addBasicBlock(const std::string &bbName, BasicBlock *bb);
  BasicBlockList& getBasicBlocks() const;

  // Creates a new Function.
  static std::unique_ptr<Function> create(std::string functionID, Module *parent);

  // Sets entry BB.
  void setEntryBB(BasicBlock *bb);
  // Gets entry BB.
  BasicBlock *getEntryBB() const;

  // Gets the num of bbs.
  size_t getNumberOfBBs() const;
  // Checks if the function is empty.
  // If it is empty, it should be optimized out.
  bool empty() const;

  const std::string& getFnID() const;

  // This removes the BB from the function.
  void removeBasicBlock(std::unique_ptr<BasicBlock> bb);

  // This prints .dot file that represents the function.
  void printCFGAsDOT(const std::string& filename) const;

  // Return true if the function is valid.
  bool isValid() const;
  // An DFS algorithm to traverse all the nodes from entry bb,
  // by following the links (tags).
  void traverse(BasicBlock *bb, std::map<BasicBlock *, bool> &visited) const;
};

// This class represents a Module for a revLANG compilation unit. It is a top
// level container for all other language objects (such as functions, basic
// blocks, instructions).
class Module {
  std::string ModuleID;
  FunctionList Functions;
  GlobalVarList GlobalVariables;

 public:
  // A name for the module must be provided when doing the construction.
  Module(std::string moduleID);
  // Prints the module to stdout.
  void dump() const;

  static std::unique_ptr<Module> create(const std::string &filename) {
    auto M = std::make_unique<Module>(filename);
    return M;
  }

  // This should be called from Function::create().
  void addFunction(const std::string& fnName, Function *f);
  FunctionList& getFunctions() const;

  // This should be called from GlobalVariable::create().
  void addGlobalVar(unsigned id, GlobalVariable *GV);
  GlobalVarList& getGlobalVars() const;
  GlobalVariable* getVarWithID(unsigned id) const;

  // Returns the number of functions within this Module.
  size_t getNumberOfFns() const;

  // This removes the function from the Module.
  void removeFunction(std::unique_ptr<Function> f);
};
