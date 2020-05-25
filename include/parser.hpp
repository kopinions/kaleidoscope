#ifndef PARSER_HPP
#define PARSER_HPP
#include "token.hpp"
#include "ast.hpp"

class parser {
public:
  std::unique_ptr<ast_node>
  parse(const std::list<std::unique_ptr<token>> &toks) {
    return std::make_unique<ast_node>();
  };
  parser() {}
};
#endif // PARSER_HPP
