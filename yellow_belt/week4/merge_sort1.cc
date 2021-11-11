#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2)
        return;

    vector<typename RandomIt::value_type> range_copy(range_begin, range_end);

    auto middle_it = begin(range_copy) + range_copy.size() / 2;

    MergeSort(begin(range_copy), middle_it);
    MergeSort(middle_it, end(range_copy));
    
    merge(begin(range_copy), middle_it,
        middle_it, end(range_copy), range_begin);
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
