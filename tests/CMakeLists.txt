add_executable(
    quicksort_test
    quicksort_test.cpp
)
target_link_libraries(
    quicksort_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(quicksort_test)