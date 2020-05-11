#include <iostream>

#include "token.hpp"
#include "stream.hpp"

class tokenizer {
  stream<token> tokenize(std::istream &in);
};
