tokenizer = executable(
  'tokenizer',
  'tokenizer.cpp',
  include_directories : [inc_src],
  dependencies : [
    gtest_dep,
    gmock_dep
  ],
  link_with : [libparser]
)
test('tokenizer', tokenizer)
