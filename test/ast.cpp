#include "ast.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

template <typename Of, typename V> inline bool instanceof (V * v) {
  if (Of *b = dynamic_cast<Of *>(v)) {
    return true;
  }
  return false;
}

TEST(ast, should_able_to_parse_variable_ast) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("id");
  translation_unit tu = parser.parse(toks);
  ASSERT_THAT(tu.size(), testing::Eq(1));
  testing::Matcher<ast::node *> matcher = testing::ResultOf(
      & instanceof <ast::variable, ast::node>, testing::IsTrue());
  EXPECT_TRUE(matcher.Matches(tu.front().get()));
}

TEST(ast, should_able_to_parse_number_ast) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("1");
  translation_unit tu = parser.parse(toks);
  ASSERT_THAT(tu.size(), testing::Eq(1));
  testing::Matcher<ast::node *> matcher = testing::ResultOf(
      & instanceof <ast::number, ast::node>, testing::IsTrue());
  EXPECT_TRUE(matcher.Matches(tu.front().get()));
}

TEST(ast, should_able_to_parse_def_ast) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def test(a) {"
                                                       "a;"
                                                       "}");
  translation_unit tu = parser.parse(toks);
  ASSERT_THAT(tu.size(), testing::Eq(1));
  testing::Matcher<ast::node *> matcher = testing::ResultOf(
      & instanceof <ast::function_definition, ast::node>, testing::IsTrue());
  EXPECT_TRUE(matcher.Matches(tu.front().get()));
}

TEST(ast, should_able_to_parse_multiple_argument_def) {
  tokenizer to;
  parser parser;
  std::list<std::unique_ptr<token>> toks = to.tokenize("def test(a,b) {"
                                                       "a+b;"
                                                       "}");
  translation_unit tu = parser.parse(toks);
  ASSERT_THAT(tu.size(), testing::Eq(1));
  testing::Matcher<ast::node *> matcher = testing::ResultOf(
      & instanceof <ast::function_definition, ast::node>, testing::IsTrue());
  EXPECT_TRUE(matcher.Matches(tu.front().get()));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
