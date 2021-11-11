#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <chrono>

using namespace std;

class Date {
public:
  Date(int year, int month, int day)
  : year_(year), month_(month), day_(day) {}

  static Date CreateFromString(const string& s) {
    istringstream is(s);

    string year, month, day;
    if(!getline(is, year, '-')
        || !getline(is, month, '-')
        || !getline(is, day))
        throw invalid_argument("Invalid Date string passed to CreateFromString");

    return Date(stoi(year), stoi(month), stoi(day));
  }

  time_t AsTimestamp() const {
    tm t;
    t.tm_sec  = 0;
    t.tm_min  = 0;
    t.tm_hour = 0;
    t.tm_mday = day_;
    t.tm_mon  = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
  }

private:
  int year_;
  int month_;
  int day_;
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
  const time_t timestamp_to = date_to.AsTimestamp();
  const time_t timestamp_from = date_from.AsTimestamp();
  static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE = Date::CreateFromString("2000-01-01");
static const Date END_DATE = Date::CreateFromString("2100-01-01");
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

int main() {
  cout.precision(25);
  vector<double> money(DAY_COUNT, .0);
  size_t num_queries;
  cin >> num_queries;

  for (size_t i = 0; i < num_queries; ++i) {
    string command, from_str, to_str;
    cin >> command >> from_str >> to_str;

    Date from = Date::CreateFromString(from_str);
    Date to = Date::CreateFromString(to_str);

    auto start_indx = ComputeDaysDiff(from, START_DATE);
    auto finish_indx = ComputeDaysDiff(to, START_DATE);
    if (command == "Earn") {
      double value;
      cin >> value;
      value /= ComputeDaysDiff(to, from) + 1;
      for (int j = start_indx; j <= finish_indx; ++j) {
        money[j] += value;
      }
    } else {
      cout << accumulate(money.begin() + start_indx, money.begin() + finish_indx + 1, 0.) << '\n';
    }
  }

  return 0;
}