#include <iostream>
#include <string>
#include "tokenizer.hpp"
#include "token.hpp"
#include "stream.hpp"

stream<token> tokenizer::tokenize(const std::istream & in) {

  std::function<std::unique_ptr<item<token>>()> func;
  std::function<std::unique_ptr<item<token>>()> func1;
  func1 = [&]{
                                                         std::string t;
                                                         std::cin >> t;
                                                         return std::make_unique<item<token>>(token(token::type::def, t),
                                                                                              stream<token>());
                                                       };
  func = [&]{
                                                         std::string t;
                                                         std::cin >> t;
                                                         return std::make_unique<item<token>>(token(token::type::def, t),
                                                                                              stream<token>(func1));
                                                       };
      return stream<token>(func);
  
} 
