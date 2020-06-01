#ifndef DEFAULT_IR_VISITOR_HPP
#define DEFAULT_IR_VISITOR_HPP
#include "ast.hpp"
#include "collector.hpp"
#include "ir_visitor.hpp"
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
#include <memory>

class llvm_ir_visitor : public ir_visitor, public collector {
public:
  llvm_ir_visitor() : Builder(TheContext) {
    TheModule = std::make_unique<llvm::Module>("my cool jit", TheContext);
  }
  virtual ~llvm_ir_visitor(){};

  virtual void visit(ast::function_definition *def) {
    llvm::Function *TheFunction =
        TheModule->getFunction(def->prototype()->identifier());
    if (!TheFunction) {
      visit(def->prototype());
    }
    visit(def->body());
  }
  virtual void visit(ast::variable *) {}
  virtual void visit(ast::number *) {}
  virtual void visit(ast::type *) {}
  virtual void visit(ast::function *f) {
    auto params = f->parameters();
    std::vector<llvm::Type *> Doubles(params.size(),
                                      llvm::Type::getDoubleTy(TheContext));
    llvm::FunctionType *FT = llvm::FunctionType::get(
        llvm::Type::getDoubleTy(TheContext), Doubles, false);

    llvm::Function *F = llvm::Function::Create(
        FT, llvm::Function::ExternalLinkage, f->identifier(), TheModule.get());

    // Set names for all arguments.
    //    unsigned Idx = 0;
    //    for (auto &Arg : F->args()) {
    //      Arg.setName(params[Idx++]);
    //    }
    values.push_back(std::make_shared<llvm::Value *>(F));
  }
  virtual void visit(ast::compound *) {}

  virtual std::list<std::shared_ptr<llvm::Value *>> collect() { return values; }

private:
  std::list<std::shared_ptr<llvm::Value *>> values;
  llvm::LLVMContext TheContext;
  llvm::IRBuilder<> Builder;
  std::unique_ptr<llvm::Module> TheModule;
  std::map<std::string, llvm::Value *> NamedValues;
};
#endif // DEFAULT_IR_VISITOR_HPP
