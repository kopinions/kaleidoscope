project(
  'kaleidoscope',
  ['c', 'cpp'],
  version : run_command(
    [find_program('python', 'python3'), 'bin/meson_get_version.py']
  ).stdout(),
  license : 'MIT',
  meson_version : '>= 0.5.0',
  default_options : ['buildtype=debug', 'b_ndebug=if-release', 'c_std=c11', 'cpp_std=c++17']
)

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')
subdir('include')
subdir('bin')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
subdir('src')
subdir('test')
