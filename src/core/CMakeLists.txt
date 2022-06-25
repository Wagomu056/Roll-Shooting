project(core_lib)

add_library(core STATIC ball_core.c math_util.c)
target_include_directories(core PUBLIC include)
