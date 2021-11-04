#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


void MyTests() {
    Person p;
    AssertEqual(p.GetFullName(1999), "Incognito");

    p.ChangeLastName(1999, "Ivanov");
    AssertEqual(p.GetFullName(1999), "Ivanov with unknown first name");
    AssertEqual(p.GetFullName(2000), "Ivanov with unknown first name");
    AssertEqual(p.GetFullName(1998), "Incognito");

    p.ChangeFirstName(1950, "Ivan");
    AssertEqual(p.GetFullName(1950), "Ivan with unknown last name");
    AssertEqual(p.GetFullName(1951), "Ivan with unknown last name");
    AssertEqual(p.GetFullName(1949), "Incognito");
    AssertEqual(p.GetFullName(2000), "Ivan Ivanov");

    p.ChangeFirstName(1998, "Nikita");
    AssertEqual(p.GetFullName(2000), "Nikita Ivanov");
    AssertEqual(p.GetFullName(1949), "Incognito");
    AssertEqual(p.GetFullName(1997), "Ivan with unknown last name");

    p.ChangeLastName(1950, "Petrov");
    AssertEqual(p.GetFullName(1950), "Ivan Petrov");
    AssertEqual(p.GetFullName(1949), "Incognito");
    AssertEqual(p.GetFullName(1998), "Nikita Petrov");
    AssertEqual(p.GetFullName(1999), "Nikita Ivanov");

}

int main() {
  TestRunner runner;
  runner.RunTest(MyTests, "MyTests");
  // добавьте сюда свои тесты
  return 0;
}
