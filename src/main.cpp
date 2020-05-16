#include "tokenizer.hpp"

int main(int argc, char **argv) {
  tokenizer to;
  std::list<token> toks = to.tokenize("abcd1234 def extern");
  for(auto it=toks.begin(); it != toks.end(); it++) {
    std::cout << "tok" << it->type() << std::endl;
  }
  
  return 0;
}
