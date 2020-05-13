#include "tokenizer.hpp"
#include "token.hpp"
#include "stream.hpp"

stream<token> tokenizer::tokenize(const std::istream & in) {
  std::function<std::unique_ptr<item<token>>()> func = []{
                                                         return std::make_unique<item<token>>(token(token::type::def, ""), stream<token>());
                                                       };
      return stream<token>(func);
  
} 
