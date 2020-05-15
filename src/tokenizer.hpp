#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>

#include "token.hpp"
#include <list>

class tokenizer {
public:
  std::list<token> tokenize(const std::string &in);
};

#endif // TOKENIZER_HPP
