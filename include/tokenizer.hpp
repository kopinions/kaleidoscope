#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "token.hpp"
#include <iostream>
#include <list>
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
  for (auto last = ctx.next(); last != std::nullopt; last = ctx.next()) {
    std::string identifier_;

    while (std::isspace(*last)) {
      last = ctx.next();
      if (last == std::nullopt) {
        return toks;
      }
    }

    if (std::isalpha(*last)) {
      identifier_ = *last;
      while (std::isalnum(*(last = ctx.next()))) {
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

    if (std::isdigit(*last) || *last == '.') {
      std::string numstr;
      do {
        numstr += *last;
        last = ctx.next();
      } while (std::isdigit(*last) || *last == '.');
      toks.push_back(std::make_unique<token>(token::type::number, numstr));
      continue;
    }

    if (*last == '#') {
      do {
        last = ctx.next();
      } while (*last != '\n' && *last != '\r' && last != std::nullopt);
      continue;
    }
    std::string singular;
    singular += *last;
    toks.push_back(
        std::make_unique<token>(token::type::singular, value(singular)));
  }

  toks.push_back(std::make_unique<token>(token::type::eof, value("")));
  return toks;
}

#endif // TOKENIZER_HPP
