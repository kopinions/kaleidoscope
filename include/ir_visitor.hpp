#ifndef IR_VISITOR_HPP
#define IR_VISITOR_HPP
#include <memory>

namespace ast {
class variable;
class number;
class type;
class compound;
class function;
class function_definition;
class function_parameter;
class call;
} // namespace ast

class ir_visitor {
public:
  virtual ~ir_visitor() = default;
  virtual void visit(ast::function_definition *) = 0;
  virtual void visit(ast::variable *) = 0;
  virtual void visit(ast::number *) = 0;
  virtual void visit(ast::type *) = 0;
  virtual void visit(ast::function *) = 0;
  virtual void visit(ast::function_parameter *) = 0;
  virtual void visit(ast::compound *) = 0;
  virtual void visit(ast::call *) = 0;
};
#endif // IR_VISITOR_HPP
