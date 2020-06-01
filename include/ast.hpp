#ifndef AST_HPP
#define AST_HPP
#include "ir_visitor.hpp"
#include <list>
#include <memory>
#include <string>

namespace ast {

class node {
public:
  virtual ~node() = default;
  virtual void accept(std::shared_ptr<ir_visitor> v) = 0;

protected:
  node(void){};
};

class variable : public node {
public:
  variable() : node() {}
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
};

class number : public node {
public:
  number() : node() {}
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
};

class type : public node {
public:
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
};

class function : public node {
public:
  function(std::string identifier,
           std::list<std::unique_ptr<ast::node>> parameters)
      : _identifier(identifier), _parameters(std::move(parameters)) {}
  virtual void accept(std::shared_ptr<ir_visitor> v) override {
    v->visit(this);
  }

  std::string identifier() {
    return _identifier;
  }

  std::list<std::reference_wrapper<ast::node>> parameters() {
    std::list<std::reference_wrapper<ast::node>> parametersRefs;
    for (auto &ptr : _parameters) {
      parametersRefs.push_back(std::ref(*ptr));
    }
    return parametersRefs;
  }

private:
  std::unique_ptr<type> returned;
  std::string _identifier;
  std::list<std::unique_ptr<ast::node>> _parameters;
};

class compound : public node {
public:
  virtual void accept(std::shared_ptr<ir_visitor> v) override {
    v->visit(this);
  }

  compound(std::list<std::unique_ptr<node>> compounded)
      : compounded(std::move(compounded)) {}

private:
  std::list<std::unique_ptr<ast::node>> compounded;
};

class function_definition : public node {
  friend class ir_visitor;
public:
  virtual void accept(std::shared_ptr<ir_visitor> v) override {
    v->visit(this);
  }

  function_definition(std::unique_ptr<function> prototype,
                      std::unique_ptr<compound> body)
      : _prototype(std::move(prototype)), _body(std::move(body)) {}

  function* prototype() { return _prototype.get(); }
  compound* body() { return _body.get(); }

private:
  std::unique_ptr<function> _prototype;
  std::unique_ptr<compound> _body;
};

} // namespace ast

#endif // AST_HPP
