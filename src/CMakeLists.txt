add_subdirectory (CodeGen)

add_executable (revLANG revLANG.cpp)

target_link_libraries (revLANG LINK_PUBLIC CodeGen)
