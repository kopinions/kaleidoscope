#include "ast.hpp"
#include "llvm_ir_visitor.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

int main(int argc, char **argv) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def test(a,b) {"
                                                       "a+b;"
                                                       "}");
  translation_unit tu = parser.parse(toks);
  auto visitor = std::make_shared<llvm_ir_visitor>();
  tu.front()->accept(visitor);
  llvm::Value **v = visitor->collect().front().get();
  (*v)->print(llvm::errs());
  fprintf(stderr, "\n");
  return 0;
}
