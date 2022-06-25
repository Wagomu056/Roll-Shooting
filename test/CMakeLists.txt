project(test_run)

find_package(GTest REQUIRED)
add_executable(test src/test.cpp src/math_util_test.cpp)

target_include_directories(test
        PRIVATE ../src/core/include)

target_link_libraries(test core)
target_link_libraries(test GTest::gtest GTest::gtest_main)