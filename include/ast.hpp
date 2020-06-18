#ifndef AST_HPP
#define AST_HPP
#include "ir_visitor.hpp"
#include <list>
#include <memory>
#include <string>
#include <vector>

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
  variable(std::string name) : _name(name) {}
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }

  std::string name() { return _name; }

private:
  std::string _name;
};

class expr : public node {
public:
  expr() {}
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
};

class call : public node {
public:
  call(std::string callee, std::vector<std::unique_ptr<node>> args)
      : _callee(callee), _args(std::move(args)) {}

  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }

  std::string callee() { return _callee; }

  std::list<std::reference_wrapper<ast::node>> args() {
    std::list<std::reference_wrapper<ast::node>> argsRefs;
    for (auto &ptr : _args) {
      argsRefs.push_back(std::ref(*ptr));
    }
    return argsRefs;
  }

private:
  std::string _callee;
  std::vector<std::unique_ptr<node>> _args;
};

class number : public node {
public:
  number(double v) : _v(v) {}
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
  double v() { return _v; }

private:
  double _v;
};

class type : public node {
public:
  void accept(std::shared_ptr<ir_visitor> v) override { v->visit(this); }
};

class function_parameter : public node {
public:
  function_parameter(std::string identifier) : _identifier(identifier) {}

  std::string identifier() { return _identifier; }

  virtual void accept(std::shared_ptr<ir_visitor> v) override {
    v->visit(this);
  }

private:
  std::string _identifier;
};

class function : public node {
public:
  function(std::string identifier,
           std::list<std::unique_ptr<ast::function_parameter>> parameters)
      : _identifier(identifier), _parameters(std::move(parameters)) {}

  virtual void accept(std::shared_ptr<ir_visitor> v) override {
    v->visit(this);
  }

  std::string identifier() { return _identifier; }

  std::list<std::reference_wrapper<ast::function_parameter>> parameters() {
    std::list<std::reference_wrapper<ast::function_parameter>> parametersRefs;
    for (auto &ptr : _parameters) {
      parametersRefs.push_back(std::ref(*ptr));
    }
    return parametersRefs;
  }

private:
  std::unique_ptr<type> returned;
  std::string _identifier;
  std::list<std::unique_ptr<ast::function_parameter>> _parameters;
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

  function *prototype() { return _prototype.get(); }
  compound *body() { return _body.get(); }

private:
  std::unique_ptr<function> _prototype;
  std::unique_ptr<compound> _body;
};

} // namespace ast

#endif // AST_HPP
