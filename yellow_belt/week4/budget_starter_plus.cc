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

static const Date START_DATE = Date::CreateFromString("1700-01-01");
static const Date END_DATE = Date::CreateFromString("2100-01-01");
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

int main() {
  cout.precision(25);
  vector<uint64_t> money(DAY_COUNT, 0);
  size_t e;
  cin >> e;

  for (size_t i = 0; i < e; ++i) {
    string date_str;
    int value;

    cin >> date_str >> value;

    Date date = Date::CreateFromString(date_str);

    auto idx = ComputeDaysDiff(date, START_DATE);

    money[idx] += value;
  }

  partial_sum(money.begin(), money.end(), money.begin());

  size_t q;
  cin >> q;

  for (size_t i = 0; i < q; ++i) {
    string from_str, to_str;
    cin >> from_str >> to_str;

    Date from = Date::CreateFromString(from_str);
    Date to = Date::CreateFromString(to_str);

    auto start_indx = ComputeDaysDiff(from, START_DATE);
    auto finish_indx = ComputeDaysDiff(to, START_DATE);

    if (start_indx > 0) {
        cout << money[finish_indx] - money[start_indx - 1] << endl;
    } else {
        cout << money[finish_indx] << endl;
    }
  }

  return 0;
}