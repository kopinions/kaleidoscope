#include "tokenizer.hpp"
#include "stream.hpp"
#include "token.hpp"
#include <iostream>
#include <optional>
#include <string>

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
    } else {
      return std::nullopt;
    }
  }

  std::optional<int> prev() {
    std::lock_guard<std::mutex> lck(_mtx);

    if (_it != _begin) {
      auto a = std::make_optional<int>(*_it);
      
      _it--;
      return a;
      
    } else {
      return std::nullopt;
    }
  }

private:
  std::mutex mutable _mtx;
  std::string::iterator mutable _it;
  std::string::iterator mutable _begin;
  std::string::iterator mutable _end;
  std::string _context;
};

std::list<token> tokenizer::tokenize(const std::string &in) {
  std::list<token> toks;
  context ctx(in);
  for(auto last=ctx.next(); last!= std::nullopt; last = ctx.next()){
    std::string identifier;
    
    while (std::isspace(*last)) {
      last = ctx.next();
      if (last == std::nullopt) {
	return toks;
      }
    }

    if (std::isalpha(*last)) {
      identifier = *last;
      while (std::isalnum(*(last = ctx.next()))) {
	identifier += *last;
      }

      std::cout << identifier << std::endl;
      if (identifier == "def") {
	toks.push_back(token(token::type::def, ""));
      } else if (identifier == "extern") {
	toks.push_back(token(token::type::ext, ""));
      } else {
	toks.push_back(token(token::type::identifier, identifier));
      }
      continue;
    }
  }
  
  return toks;
}
