project(core_lib)

add_library(core STATIC math_util.c util.c)
target_include_directories(core PUBLIC include)
