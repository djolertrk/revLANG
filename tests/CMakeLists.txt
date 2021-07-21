## This file manages tests (both regression and unit).

# This is simple test with regular invoke of the program.
# NOTE: This is a dummy test. This is the way we can check for the regressions.
add_test(compiler_invoke ${CMAKE_BINARY_DIR}/bin/revLANG)
set_tests_properties(compiler_invoke
    PROPERTIES PASS_REGULAR_EXPRESSION "=== revLang interpreter ===")
set_tests_properties(compiler_invoke
    PROPERTIES PASS_REGULAR_EXPRESSION "Module before the optimizations")
set_tests_properties(compiler_invoke
    PROPERTIES PASS_REGULAR_EXPRESSION "Module after the optimizations")

# Unit tests.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

target_include_directories (CodeGen PUBLIC ${REVLANG_MAIN_SRC_DIR}/include)

add_executable(UnitTest UnitTests.cpp)
target_link_libraries (UnitTest LINK_PUBLIC CodeGen)
add_test(unitTest UnitTest)
