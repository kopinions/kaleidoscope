#ifndef PARSER_HPP
#define PARSER_HPP
#include "ast.hpp"
#include "token.hpp"
#include <list>

using translation_unit = std::list<std::unique_ptr<ast::node>>;
class parser {
public:
  translation_unit parse(const std::list<std::unique_ptr<token>> &toks) {
    translation_unit tu;
    for (auto it = toks.begin(); it != toks.end(); it++) {
      switch ((*it)->type()) {
      case token::type::identifier:
        tu.push_back(std::make_unique<ast::variable>());
        break;
      case token::type::number:
        tu.push_back(std::make_unique<ast::number>());
        break;
      default:
        break;
      }
    }

    return tu;
  };
  parser() {}
};
#endif // PARSER_HPP
