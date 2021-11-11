#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
using namespace std;

template <typename T>
void PrintVector(vector<T>& elements) {
  for (T& e : elements) {
    cout << e << " ";
  }
  cout << endl;
}

int main() {
  int n;

  cin >> n;

  vector<int> nums(n);

  iota(nums.rbegin(), nums.rend(), 1);

  do {
    PrintVector(nums);
  } while (prev_permutation(nums.begin(), nums.end()));

  return 0;
}
