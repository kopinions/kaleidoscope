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
      case token::type::def: {
        it++;
        std::list<std::unique_ptr<ast::node>> args;
        if ((*it)->type() == token::type::identifier) {
          it++;
          args.push_back(std::make_unique<ast::variable>());
          it++;
        }
        it++;
        auto prototype = std::make_unique<ast::function>((*it)->val()->string(),
                                                         std::move(args));
        it++;
        auto body = std::make_unique<ast::compound>();
        tu.push_back(std::make_unique<ast::function_definition>(
            std::move(prototype), std::move(body)));
        it++;
      } break;
      default:
        continue;
      }
    }

    return tu;
  };
  parser() {}
};
#endif // PARSER_HPP
