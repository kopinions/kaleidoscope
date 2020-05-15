#include "tokenizer.hpp"
#include "stream.hpp"
#include "token.hpp"
#include <iostream>
#include <string>

std::list<token> tokenizer::tokenize(const std::string &in) {
  std::list<token> toks;
  toks.push_back(token(token::type::number, ""));
  return toks;
}
