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

void CreateBasicRational() {
  Rational r;
  AssertEqual(r.Numerator(), 0);
  AssertEqual(r.Denominator(), 1);

  r = {5, 2};
  AssertEqual(r.Numerator(), 5);
  AssertEqual(r.Denominator(), 2);

  r = {-2, -5};
  AssertEqual(r.Numerator(), 2);
  AssertEqual(r.Denominator(), 5);
}

void CreateZeroRational() {
  Rational r = {0, 1};
  AssertEqual(r.Numerator(), 0);
  AssertEqual(r.Denominator(), 1);

  r = {0, -5};
  AssertEqual(r.Numerator(), 0);
  AssertEqual(r.Denominator(), 1);
}

void CreateUnexaminedRational() {
  Rational r = {10, 5};
  AssertEqual(r.Numerator(), 2);
  AssertEqual(r.Denominator(), 1);

  r = {3, 6};
  AssertEqual(r.Numerator(), 1);
  AssertEqual(r.Denominator(), 2);
}

void CreateNegativeRational() {
  Rational r = {-3, 2};
  AssertEqual(r.Numerator(), -3);
  AssertEqual(r.Denominator(), 2);

  r = {2, -3};
  AssertEqual(r.Numerator(), -2);
  AssertEqual(r.Denominator(), 3);
}

int main() {
  TestRunner runner;
  runner.RunTest(CreateBasicRational, "CreateBasicRational");
  runner.RunTest(CreateZeroRational, "CreateZeroRational");
  runner.RunTest(CreateUnexaminedRational, "CreateUnexaminedRational");
  runner.RunTest(CreateNegativeRational, "CreateNegativeRational");
  // ???????????????? ???????? ???????? ??????????
  return 0;
}
