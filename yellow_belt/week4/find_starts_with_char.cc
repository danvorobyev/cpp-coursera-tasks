#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {
    auto first_not_less = lower_bound(range_begin, range_end, string(1, prefix));
    auto first_greater = lower_bound(range_begin, range_end, string(1, static_cast<char>(prefix+1)));

    if (first_not_less == first_greater)
        return make_pair(first_not_less, first_not_less);

    return make_pair(first_not_less, first_greater);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
  
  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;
  
  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
