cc = meson.get_compiler('c')

sources = files(
  'src/lv2_interface.c'
)

deps = [
  dependency('lv2', required: true),
  cc.find_library('m', required: true),
]

shared_library('mushroom', sources, dependencies: deps)
