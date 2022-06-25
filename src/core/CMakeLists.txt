project(core_lib)

add_library(core STATIC math_util.c)
target_include_directories(core PUBLIC include)
