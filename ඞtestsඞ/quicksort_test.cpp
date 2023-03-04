#include "ඞquicksortඞ/parallel.hpp"
#include "ඞquicksortඞ/unparallel.hpp"
#include "gtest/gtest.h"
#include <cstdlib>
#include <vector>

bool is_sorted(std::vector<int> &&v) {
  for (int i = 0; i < ((int)v.size()) - 1; i++)
    if (v[i] > v[i + 1])
      return false;
  return true;
};

std::vector<int> generator(int n) {
  std::vector<int> v(n);
  for (auto &x : v) {
    x = rand();
  }
  return v;
}

std::vector<int>::iterator partition(std::vector<int>::iterator first,
                                     std::vector<int>::iterator last) {
  auto end = last - 1;
  auto x = *end;
  auto i = first;
  for (auto j = first; j < end; j++) {
    if (*j <= x) {
      std::swap(*i, *j);
      i++;
    }
  }
  std::swap(*i, *end);
  return i;
}

std::vector<int> Od(int n) {
  std::vector<int> v(n);
  v = generator(n);
  quicksort(v.begin(), v.end(), partition);
  return v;
};

std::vector<int> POd(int n) {
  std::vector<int> v(n);
  v = generator(n);
  pquicksort(v.begin(), v.end(), partition);
  return v;
};

TEST(QsortTest, ZeroItems) { EXPECT_TRUE(is_sorted(Od(0))); }
TEST(QsortTest, OneItem) { EXPECT_TRUE(is_sorted(Od(1))); }
TEST(QsortTest, TwoItems) { EXPECT_TRUE(is_sorted(Od(2))); }
TEST(QsortTest, TreeItems) { EXPECT_TRUE(is_sorted(Od(3))); }
TEST(QsortTest, FourItems) { EXPECT_TRUE(is_sorted(Od(4))); }
TEST(QsortTest, TenItems) { EXPECT_TRUE(is_sorted(Od(10))); }

TEST(QsortTest, ManyItems) {
  EXPECT_TRUE(is_sorted(Od(1e2)));
  EXPECT_TRUE(is_sorted(Od(1e3)));
  EXPECT_TRUE(is_sorted(Od(1e4)));
  EXPECT_TRUE(is_sorted(Od(1e5)));
  EXPECT_TRUE(is_sorted(Od(1e6)));
}

TEST(PQsortTest, ManyItems) {
  EXPECT_TRUE(is_sorted(POd(0)));
  EXPECT_TRUE(is_sorted(POd(1e0)));
  EXPECT_TRUE(is_sorted(POd(1e1)));
  EXPECT_TRUE(is_sorted(POd(1e2)));
  EXPECT_TRUE(is_sorted(POd(1e3)));
  EXPECT_TRUE(is_sorted(POd(1e4)));
  EXPECT_TRUE(is_sorted(POd(1e5)));
  EXPECT_TRUE(is_sorted(POd(1e6)));
}