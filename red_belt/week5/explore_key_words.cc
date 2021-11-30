#include "test_runner.h"
#include "profile.h"

#include <map>
#include <set>
#include <string>
#include <utility>
#include <iterator>
#include <future>
#include <thread>
using namespace std;

#define MAX_CHUNK_SIZE 5000

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto& [key, value] : other.word_frequences) {
      word_frequences[key] += value;
    }
  }
};

vector<string> SplitLine(const string& line) {
  istringstream is(line);
  return {istream_iterator<string>(is), istream_iterator<string>()};
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats result;
  for (const auto& word : SplitLine(line)) {
    if (key_words.find(word) != key_words.end()) {
      result.word_frequences[word]++;
    }
  }
  return result;
}

Stats ExploreChunk(const set<string>& key_words, vector<string>&& chunk) {
  Stats result;
  for (const string& line : chunk)
    result += ExploreLine(key_words, line);
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  vector<string> chunk;
  chunk.reserve(MAX_CHUNK_SIZE);
  string line;

  vector<future<Stats>> futures;
  while(getline(input, line)) {
    chunk.push_back(line);
    if (chunk.size() == MAX_CHUNK_SIZE) {
      futures.push_back(async(ExploreChunk, ref(key_words), move(chunk)));
    }
  }

  Stats result;

  if (!chunk.empty()) {
    result += ExploreChunk(key_words, move(chunk));
  }

  for (auto& f : futures) {
    result += f.get();
  }
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
