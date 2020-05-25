#ifndef AST_HPP
#define AST_HPP
namespace ast {

class node {
public:
  virtual ~node() = default;

protected:
  node(void){};
};

class variable : public node {
public:
  variable() : node() {}
};

} // namespace ast

#endif // AST_HPP
