#include "tokenizer.hpp"
#include "stream.hpp"
#include "token.hpp"
#include <iostream>
#include <string>

std::unique_ptr<std::list<token>> tokenizer::tokenize(const std::string &in) {
  auto toks = new std::list<token>();
  toks->push_back(token(token::type::number, ""));
  return std::move(std::unique_ptr<std::list<token>>(toks));
}
