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
        tu.push_back(identifier_handler(it));
        break;
      case token::type::number:
        tu.push_back(std::make_unique<ast::number>((*it)->val()->d()));
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
  std::unique_ptr<ast::node>
  identifier_handler(std::list<std::unique_ptr<token>>::const_iterator &it) {
    auto id = *(*it).get();
    // eat identifier
    if ((*(++it))->type() != token::type::lparen) {
      return std::make_unique<ast::variable>(id.val()->string());
    }

    it++; // eat (
    it++; // eat parameter
    it++; // eat )
    return std::make_unique<ast::call>();

  }

  std::unique_ptr<ast::function_definition>
  function_definition(std::list<std::unique_ptr<token>>::const_iterator &it) {
    it++; // def
    std::string funid = (*it)->val()->string();
    it++; // identifier
    std::list<std::unique_ptr<ast::function_parameter>> args;
    if ((*it)->type() == token::type::lparen) {
      it++;
      while ((*it)->type() != token::type::rparen) {
        if ((*it)->type() == token::type::identifier) {
          args.push_back(std::make_unique<ast::function_parameter>(
              (*it)->val()->string()));
        }
        it++;
      }
    }
    it++; // )
    it++; // {
    auto prototype = std::make_unique<ast::function>(funid, std::move(args));
    std::list<std::unique_ptr<ast::node>> compounded;
    while ((*it)->type() != token::type::rbracket) {
      compounded.push_back(std::make_unique<ast::variable>(""));
      it++;
    }
    auto body = std::make_unique<ast::compound>(std::move(compounded));
    return std::make_unique<ast::function_definition>(std::move(prototype),
                                                      std::move(body));
  }
};
#endif // PARSER_HPP
