#pragma once
template <class RandomIt, class SchemePolicy>
void quicksort(RandomIt first, RandomIt last, SchemePolicy &&partition) {
  if (last - first > 1) {
    RandomIt pivot = partition(first, last);
    quicksort(first, pivot, partition);
    quicksort(pivot, last, partition);
  }
}