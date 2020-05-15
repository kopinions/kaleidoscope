#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>

#include "stream.hpp"
#include "token.hpp"

class tokenizer {
public:
  stream<token> tokenize(const std::istream &in);
};

#endif // TOKENIZER_HPP
