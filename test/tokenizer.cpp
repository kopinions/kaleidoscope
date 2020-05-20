#include "tokenizer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(tokenizer, should_able_to_parse_def_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def");
  ASSERT_THAT(toks.size(), 1);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::def));
}

TEST(tokenizer, should_able_to_parse_extern_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("extern");
  ASSERT_THAT(toks.size(), 1);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::ext));
}

TEST(tokenizer, should_able_to_parse_identifier_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("id");
  ASSERT_THAT(toks.size(), 1);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::identifier));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
