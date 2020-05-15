#include "tokenizer.hpp"

int main(int argc, char **argv) {
  tokenizer to;
  std::list<token> toks = to.tokenize("");
  for(auto it=toks.begin(); it != toks.end(); it++) {
    std::cout << "tok" << std::endl;
  }
  
  return 0;
}
