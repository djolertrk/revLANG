# NOTE: This should work with prior cmake versions as well.
cmake_minimum_required (VERSION 2.8.11)
project (revLANG)

# Remember this, so we can use it in the subdirs.
set(REVLANG_MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# The src/ contains all the source code.
add_subdirectory (src)
