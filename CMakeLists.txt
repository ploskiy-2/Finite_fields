cmake_minimum_required(VERSION 3.11)
project(Finite_fields)

# Include subdirectories
add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME gftest COMMAND tests)
