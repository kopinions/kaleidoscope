#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>

#include "token.hpp"
#include "stream.hpp"

class tokenizer {
 public:
  stream<token> tokenize(const std::istream &in);
};

#endif// TOKENIZER_HPP
