#include "tokenizer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(tokenizer, should_able_to_parse_def_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def");
  ASSERT_THAT(toks.size(), 2);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::def));
}

TEST(tokenizer, should_able_to_parse_extern_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("extern");
  ASSERT_THAT(toks.size(), 2);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::ext));
}

TEST(tokenizer, should_able_to_parse_identifier_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("id");
  ASSERT_THAT(toks.size(), 2);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::identifier));
}

TEST(tokenizer, should_able_to_parse_number_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("1");
  ASSERT_THAT(toks.size(), 2);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::number));
}

TEST(tokenizer, should_able_to_parse_comment) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("#this is a comment\n");
  ASSERT_THAT(toks.size(), 1);
  toks = to.tokenize("#this is a comment without newline");
  ASSERT_THAT(toks.size(), 1);
}

TEST(tokenizer, should_able_to_return_eof_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("");
  ASSERT_THAT(toks.size(), 1);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::eof));
}

TEST(tokenizer, should_able_to_return_singular_token) {
  tokenizer to;
  std::list<std::unique_ptr<token>> toks = to.tokenize("a + b");
  ASSERT_THAT(toks.size(), 4);
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::identifier));
  toks.pop_front();
  ASSERT_THAT(toks.front()->type(), testing::Eq(token::type::singular));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
