#pragma once

#include <thread>
#include "unparallel.hpp"

template <class RandomIt, class SchemePolicy>
void pquicksort(RandomIt first, RandomIt last, SchemePolicy &&partition) {
  if (first < last) {
    if (last - first < 1'000'000) {
      quicksort(first, last, partition);
      return;
    }
    RandomIt pivot = partition(first, last);
    auto t1 = std::thread(
        [first, pivot, partition] { pquicksort(first, pivot, partition); });
    auto t2 = std::thread(
        [last, pivot, partition] { pquicksort(pivot, last, partition); });
    t1.join();
    t2.join(); 
  }
}