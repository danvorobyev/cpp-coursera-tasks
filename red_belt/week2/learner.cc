#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "profile.h"

using namespace std;

class Learner {
 private:
  set<string> strings;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    //LOG_DURATION("Loop");
    for (const auto& word : words) {
      if (strings.find(word) == strings.end()) {
        ++newWords;
        strings.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    //LOG_DURATION("KnownWords");
    return {strings.begin(), strings.end()};
  }
};


int main() {
  LOG_DURATION("Main");
  Learner learner;
  string line;
  vector<string> strings(10000);
  int i = 0;
  for (auto& s : strings) {
    s = to_string(i++);
  }
  for (int i = 0; i < 10; i++) {
    learner.Learn(strings);
    learner.KnownWords();
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}