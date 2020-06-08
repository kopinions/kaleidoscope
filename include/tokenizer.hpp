#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "token.hpp"
#include "utils.hpp"
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include <string>

class tokenizer {
public:
  std::list<std::unique_ptr<token>> tokenize(const std::string &in);
};

class context {
public:
  context(const std::string &&in) {
    _context = in;
    _it = _context.begin();
    _begin = _context.begin();
    _end = _context.end();
  }

  context(const std::string &in) {
    _context = in;
    _it = _context.begin();
    _begin = _context.begin();
    _end = _context.end();
  }

  std::optional<int> next() const {
    std::lock_guard<std::mutex> lck(_mtx);

    if (_it != _end) {
      auto a = std::make_optional<int>(*_it);
      _it++;
      return a;
    }

    return std::nullopt;
  }

  std::optional<int> prev() {
    std::lock_guard<std::mutex> lck(_mtx);

    if (_it != _begin) {
      auto a = std::make_optional<int>(*_it);

      _it--;
      return a;
    }
    return std::nullopt;
  }

private:
  std::mutex mutable _mtx;
  std::string::iterator mutable _it;
  std::string::iterator mutable _begin;
  std::string::iterator mutable _end;
  std::string _context;
};



std::list<std::unique_ptr<token>> tokenizer::tokenize(const std::string &in) {
  std::list<std::unique_ptr<token>> toks;
  context ctx(in);
  for (auto last = ctx.next(); last != std::nullopt; ) {
    std::string identifier_;

    while (utils::isspace(last)) {
      last = ctx.next();
      if (last == std::nullopt) {
        break;
      }
    }

    if (utils::isalpha(last)) {
      identifier_ = *last;
      while ((last = ctx.next()) != std::nullopt && utils::isalnum(last)) {
        identifier_ += *last;
      }

      if (identifier_ == "def") {
        toks.push_back(std::make_unique<token>(token::type::def, value("def")));
      } else if (identifier_ == "extern") {
        toks.push_back(
            std::make_unique<token>(token::type::ext, value("extern")));
      } else {
        toks.push_back(std::make_unique<token>(token::type::identifier,
                                               value(identifier_)));
      }
      continue;
    }

    if (utils::isdigit(last) || *last == '.') {
      std::string numstr;
      do {
        numstr += *last;
        last = ctx.next();
      } while (utils::isdigit(last) || *last == '.');
      toks.push_back(std::make_unique<token>(token::type::number, numstr));
      continue;
    }

    if (*last == '#') {
      do {
        last = ctx.next();
      } while (*last != '\n' && *last != '\r' && last != std::nullopt);
      continue;
    }

    switch (*last) {
    case '+':
      toks.push_back(std::make_unique<token>(token::type::plus,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case '(':
      toks.push_back(std::make_unique<token>(token::type::lparen,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case ')':
      toks.push_back(std::make_unique<token>(token::type::rparen,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case '{':
      toks.push_back(std::make_unique<token>(token::type::lbracket,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case '}':
      toks.push_back(std::make_unique<token>(token::type::rbracket,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case ';':
      toks.push_back(std::make_unique<token>(token::type::semicolon,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    case ',':
      toks.push_back(std::make_unique<token>(token::type::comma,
                                             value(std::string(1, *last))));
      last = ctx.next();
      break;
    default:
      continue;
    }
  }

  toks.push_back(std::make_unique<token>(token::type::eof, value("")));
  return toks;
}

#endif // TOKENIZER_HPP
