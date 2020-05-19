#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tokenizer.hpp"
TEST(tokenizer, should_able_to_parse_def_token) {
  tokenizer to;
  std::list<token> toks = to.tokenize("def");
  ASSERT_THAT(toks.size(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
