#include <set>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> strings; 

    auto it = s.begin();

    while (it != s.end()) {
        auto start_it = it;
        it = find(it, s.end(), ' ');
        strings.push_back({start_it, it});
        if (it != s.end())
            it++;
    }
    return strings;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
