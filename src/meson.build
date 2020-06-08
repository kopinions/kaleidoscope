inc_src = include_directories('.')

parser_files = files(
)

libparser = static_library(
  'parser',
  [parser_files],
  include_directories : [inc_src, inc_headers],
  dependencies : []
)

main = executable(
  'main',
  'main.cpp',
  c_args : [],
  cpp_args : [],
  dependencies : [
  llvm_dep
  ],
  include_directories : [inc_src, inc_headers],
  link_with : [libparser],
  build_by_default : true
)
