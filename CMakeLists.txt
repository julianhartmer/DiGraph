cmake_minimum_required(VERSION 3.10)
project(DiGraph C)

add_library(digraph SHARED digraph.c)
set_property(TARGET digraph PROPERTY C_STANDARD 90)

target_include_directories(digraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)
