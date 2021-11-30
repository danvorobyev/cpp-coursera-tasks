#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include "test_runner.h"
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;

    vector<typename RandomIt::value_type> range_copy(
      make_move_iterator(range_begin), 
      make_move_iterator(range_end));

    auto first_it = begin(range_copy) + range_copy.size() / 3;
    auto second_it = begin(range_copy) + range_copy.size() * 2 / 3;

    MergeSort(begin(range_copy), first_it);
    MergeSort(first_it, second_it);
    MergeSort(second_it, end(range_copy));

    vector<typename RandomIt::value_type> tmp;

    merge(
      make_move_iterator(range_copy.begin()),
      make_move_iterator(first_it),
      make_move_iterator(first_it), 
      make_move_iterator(second_it), 
      back_inserter(tmp));

    merge(
      make_move_iterator(tmp.begin()), 
      make_move_iterator(tmp.end()), 
      make_move_iterator(second_it), 
      make_move_iterator(range_copy.end()),
      range_begin);
}


void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}