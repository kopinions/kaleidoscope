files_lexer = files(
  'token.hpp',
  'token.cpp',
  'main.cpp',
  'stream.hpp',
  'tokenizer.hpp',
  'tokenizer.cpp'
)

glsl_compiler = executable(
  'main',
  files_lexer,
  c_args : [],
  cpp_args : [],
  dependencies : [],
  include_directories : [],
  link_with : [],
  #link_args : ['-Wl,-sysroot,/usr/lib','-Wl,-L,/usr/local/Cellar/llvm/10.0.0_3/lib:/usr/lib:/usr/local/lib'],
  build_by_default : true
)
