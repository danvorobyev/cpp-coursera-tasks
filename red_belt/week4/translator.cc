#include "test_runner.h"
#include <string>
#include <map>
#include <deque>

using namespace std;


class Translator {
public:
  void Add(string_view source, string_view target) {
    const string_view src = find_or_create(source);
    const string_view tgt = find_or_create(target);
    forward_translations[src] = tgt;
    backward_translations[tgt] = src;
  }
  string_view TranslateForward(string_view source) const {
    return find_view(forward_translations, source);
  }
  string_view TranslateBackward(string_view target) const {
    return find_view(backward_translations, target);
  }

private:
  map<string_view, string_view> forward_translations;
  map<string_view, string_view> backward_translations;
  deque<string> words;

  const string_view find_or_create(string_view s) {
    for (const auto* translation_ptr : {&forward_translations, &backward_translations}) {
      auto it = translation_ptr->find(s);
      if (it != translation_ptr->end())
        return it->first;
    }
    return words.emplace_back(s);
  }

  string_view find_view(const map<string_view, string_view>& m, string_view s) const {
    auto it = m.find(s);
    if (it != m.end())
      return it->second;
    return {};
  }
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");

  ASSERT_EQUAL(translator.TranslateBackward("window"), "okno");

  translator.Add(string("okno"), string("nowindow"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "nowindow");

  ASSERT_EQUAL(translator.TranslateBackward("nowindow"), "okno");

  ASSERT_EQUAL(translator.TranslateBackward("window"), "okno");

  translator.Add(string("stol"), string("table"));
  translator.Add(string("aaaa"), string("table"));
  translator.Add(string("aaaa"), string("table"));

  ASSERT_EQUAL(translator.TranslateBackward("table"), "aaaa");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
