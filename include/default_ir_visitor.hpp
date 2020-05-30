#ifndef DEFAULT_IR_VISITOR_HPP
#define DEFAULT_IR_VISITOR_HPP
#include "ast.hpp"
#include "collector.hpp"
#include "ir_visitor.hpp"
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

class default_ir_visitor : public ir_visitor, public collector {
public:
  default_ir_visitor() {}
  virtual ~default_ir_visitor(){};

  virtual void visit(ast::function_definition *def) {
    visit(def->prototype());
    visit(def->body());
  }
  virtual void visit(ast::variable *) {}
  virtual void visit(ast::number *) {}
  virtual void visit(ast::type *) {}
  virtual void visit(ast::function * f) {
//    Function *TheFunction = TheModule->getFunction(f->getName());
  }
  virtual void visit(ast::compound *) {}

  virtual std::list<std::shared_ptr<llvm::Value*>> collect() {
    return values;
  }
private:
  std::list<std::shared_ptr<llvm::Value*>> values;
//  static llvm::LLVMContext TheContext;
//  static llvm::IRBuilder<> Builder(TheContext);
//  static std::unique_ptr<llvm::Module> TheModule;
//  static std::map<std::string, llvm::Value *> NamedValues;
};
#endif // DEFAULT_IR_VISITOR_HPP
