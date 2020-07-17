#ifndef DEFAULT_IR_VISITOR_HPP
#define DEFAULT_IR_VISITOR_HPP
#include "ast.hpp"
#include "collector.hpp"
#include "ir_visitor.hpp"
#include <iostream>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>

class llvm_ir_visitor : public ir_visitor,
                        public collector,
                        public std::enable_shared_from_this<llvm_ir_visitor>
{
public:
  llvm_ir_visitor() : Builder(TheContext), NamedValues() {
    TheModule = std::make_unique<llvm::Module>("my cool jit", TheContext);
  }
  virtual ~llvm_ir_visitor(){};

  virtual void visit(ast::function_definition *def) {
    if (!TheModule->getFunction(def->prototype()->identifier())) {
      visit(def->prototype());
    }

    llvm::Function *TheFunction =
        TheModule->getFunction(def->prototype()->identifier());

    llvm::BasicBlock *BB =
        llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
    Builder.SetInsertPoint(BB);

    NamedValues.clear();
    for (auto &Arg : TheFunction->args()) {
      NamedValues[std::string(Arg.getName())] = &Arg;
    }

    auto visitor = shared_from_this();
    def->body()->accept(visitor);
    auto statements = visitor->collect();
    if (llvm::Value *RetVal =
            (statements.empty()
                 ? llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0))
                 : (*(statements.back().get())))) {

      Builder.CreateRet(RetVal);
      llvm::verifyFunction(*TheFunction);
      values.push_back(std::make_shared<llvm::Value *>(TheFunction));
      return;
    }

    TheFunction->eraseFromParent();
  }
  virtual void visit(ast::variable *v) {
    llvm::Value *V = NamedValues[v->name()];
    if (!V) {
      std::cout << "error no v";
    }
    values.push_back(std::make_shared<llvm::Value *>(V));
  }
  virtual void visit(ast::number *n) {
    auto v = llvm::ConstantFP::get(TheContext, llvm::APFloat((double)n->v()));
    values.push_back(std::make_shared<llvm::Value *>(v));
  }
  virtual void visit(ast::type *) {}
  virtual void visit(ast::function *f) {
    auto params = f->parameters();
    std::vector<llvm::Type *> Doubles(params.size(),
                                      llvm::Type::getDoubleTy(TheContext));
    llvm::FunctionType *FT = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(TheContext), Doubles, false);

    llvm::Function *F = llvm::Function::Create(
        FT, llvm::Function::ExternalLinkage, f->identifier(), TheModule.get());

    for (auto &Arg : F->args()) {
      std::reference_wrapper<ast::function_parameter> a = params.front();
      Arg.setName(a.get().identifier());
      params.pop_front();
    }
  }

  virtual void visit(ast::function_parameter *){};

  virtual void visit(ast::compound *) {}
  virtual void visit(ast::expr *) {}

  virtual void visit(ast::call *c) {
    llvm::Function *CalleeF = TheModule->getFunction(c->callee());
    if (!CalleeF)
      return;

    // If argument mismatch error.
    auto Args = c->args();
    if (CalleeF->arg_size() != Args.size())
      return;

    std::vector<llvm::Value *> ArgsV;
    for (ast::node& arg : Args) {
      auto visitor = shared_from_this();
      arg.accept(visitor);
      auto r = visitor->collect().back().get();
      ArgsV.push_back(*r);
    }

    values.push_back(std::make_shared<llvm::Value *>(
        Builder.CreateCall(CalleeF, ArgsV, "calltmp")));
  }

  virtual std::list<std::shared_ptr<llvm::Value *>> collect() { return values; }

private:
  std::list<std::shared_ptr<llvm::Value *>> values;
  llvm::LLVMContext TheContext;
  llvm::IRBuilder<> Builder;
  std::unique_ptr<llvm::Module> TheModule;
  std::map<std::string, llvm::Value *> NamedValues;
};
#endif // DEFAULT_IR_VISITOR_HPP
