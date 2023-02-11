plugin_name = 'mushroom'
data_files = ['manifest.ttl', 'mushroom.ttl']
sources = files(
  'src/lv2_interface.cpp',
  'src/plugin_handle.cpp'
)

deps = [
  dependency('lv2', required: true),
  cpp.find_library('m', required: true),
]

shared_library(
  plugin_name, 
  sources, 
  dependencies: deps,
  install: true,
  install_dir: lv2_dir / plugin_name,
)

foreach file : data_files
  configure_file(
    copy: true,
    input: file,
    install_dir: lv2_dir / plugin_name,
    output: file,
  )
endforeach
