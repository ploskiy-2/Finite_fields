add_executable(tests maintest.c)

target_link_libraries(tests gf)

target_compile_options(tests PRIVATE -Wall -g)
