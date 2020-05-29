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
        tu.push_back(function_definition(it));
      } break;
      default:
        continue;
      }
    }

    return tu;
  };
  parser() {}

private:
  std::unique_ptr<ast::function_definition>
  function_definition(std::list<std::unique_ptr<token>>::const_iterator &it) {
    it++; // def
    std::list<std::unique_ptr<ast::node>> args;
    if ((*it)->type() == token::type::lparen) {
      it++;
      while((*it)->type() != token::type::rparen) {
        args.push_back(std::make_unique<ast::variable>());
        it++;
      }
    }
    it++; // {
    auto prototype = std::make_unique<ast::function>((*it)->val()->string(),
                                                     std::move(args));
    std::list<std::unique_ptr<ast::node>> compounded;
    while((*it)->type() != token::type::rbracket) {
      compounded.push_back(std::make_unique<ast::variable>());
      it++;
    }
    auto body = std::make_unique<ast::compound>(std::move(compounded));
    return std::make_unique<ast::function_definition>(std::move(prototype),
                                                      std::move(body));
  }
};
#endif // PARSER_HPP
