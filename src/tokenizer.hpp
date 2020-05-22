#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "token.hpp"
#include <memory>
#include <iostream>
#include <list>

class tokenizer {
public:
  std::list<std::unique_ptr<token>> tokenize(const std::string &in);
};

#endif // TOKENIZER_HPP
