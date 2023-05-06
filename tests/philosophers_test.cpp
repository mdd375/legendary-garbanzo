#include "./philosophers/philosophers.hpp"
#include "gtest/gtest.h"

TEST(Sponger1, Sponger) { EXPECT_TRUE(solve(1)); }
TEST(Sponger2, Sponger) { EXPECT_TRUE(solve(2)); }
TEST(Sponger3, Sponger) { EXPECT_TRUE(solve(3)); }
TEST(Sponger5, Sponger) { EXPECT_TRUE(solve(5)); }
TEST(Sponger8, Sponger) { EXPECT_TRUE(solve(8)); }