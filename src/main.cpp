#include "tokenizer.hpp"
  
int main(int argc, char** argv) {
  tokenizer to;
  to.tokenize(std::cin).get();
  return 0;
}
