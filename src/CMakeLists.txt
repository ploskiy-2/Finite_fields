add_library(gf STATIC ff.c ff.h)

target_include_directories(gf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
