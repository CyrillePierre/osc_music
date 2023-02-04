plugin_name = 'mushroom'
sources = files('src/lv2_interface.c')
data_files = [ 'manifest.ttl', 'mushroom.ttl' ]

deps = [
  dependency('lv2', required: true),
  cc.find_library('m', required: true),
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
