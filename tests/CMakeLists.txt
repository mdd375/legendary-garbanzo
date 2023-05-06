add_executable(
    quicksort_test
    quicksort_test.cpp
)
target_link_libraries(
    quicksort_test
    GTest::gtest_main
)

add_executable(
    philosophers_test
    philosophers_test.cpp
)
target_link_libraries(
    philosophers_test
    philosophers
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(quicksort_test)
gtest_discover_tests(philosophers_test)