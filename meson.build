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
subdir('src')
