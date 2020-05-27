#ifndef AST_HPP
#define AST_HPP
#include <memory>
#include <list>
#include <string>

namespace ast {

class node {
public:
  virtual ~node() = default;
//  virtual node(const node &) = default;
//  virtual node(const node &&) = default;

protected:
  node(void){};
};

class variable : public node {
public:
  variable() : node() {}
};

class number : public node {
public:
  number() : node() {}
};

class type : public node {};

class function : public node {
public:
  function(std::string identifier, std::list<std::unique_ptr<ast::node>> parameters)
      : identifier(identifier), parameters(std::move(parameters)) {}

private:
  std::unique_ptr<type> returned;
  std::string identifier;
  std::list<std::unique_ptr<ast::node>> parameters;
};

class compound : public node {
public:
  compound(std::list<std::unique_ptr<node>> compounded)
      : compounded(std::move(compounded)) {

  }
private:
  std::list<std::unique_ptr<ast::node>> compounded;
};

class function_definition : public node {
public:
  function_definition(std::unique_ptr<function> prototype, std::unique_ptr<compound> body)
      : prototype(std::move(prototype)),
        body(std::move(body)) {}

private:
  std::unique_ptr<function> prototype;
  std::unique_ptr<compound> body;
};

} // namespace ast

#endif // AST_HPP
