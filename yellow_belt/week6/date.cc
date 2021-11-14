#include "date.h"


Date ParseDate(istream &input) {

    int year, month, day;
    char delim1, delim2;
    input >> year >> delim1 >> month >> delim2 >> day;
    if (!input || delim1 != '-' || delim2 != '-') {
        throw runtime_error("Wrong date format");
    }
    return Date(year, month, day);
}

ostream &operator<<(ostream &output, const Date &date) {
    return output << setw(4) << setfill('0') << date.year
                  << "-" << setw(2) << setfill('0') << date.month
                  << "-" << setw(2) << setfill('0') << date.day;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return tie(lhs.year, lhs.month, lhs.day) <= tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (year < 0 || year > 9999) {
        throw runtime_error("Year value is invalid: " + to_string(new_year));
    }
    if (new_month < 1 || new_month > 12) {
        throw runtime_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day < 1 || new_day > 31) {
        throw runtime_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
}

Date::Date() : year(0), month(1), day(1) {}