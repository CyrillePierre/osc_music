cmake_minimum_required(VERSION 3.11)

add_library(mushroom
	src/lv2_interface.c
)
target_compile_options(mushroom PRIVATE -Wall -Wextra)
