#include "ast.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(ast, should_able_to_parse_def_ast) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def id");
  std::unique_ptr<ast_node> root = parser.parse(toks);
  ASSERT_THAT(root, testing::NotNull());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
