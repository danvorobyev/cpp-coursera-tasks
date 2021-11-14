#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

class Date {
public:
    Date(int new_year, int new_month, int new_day);

    Date();

    int getYear() const { return year; }

    int getMonth() const { return month; }

    int getDay() const { return day; }

    friend bool operator<(const Date &lhs, const Date &rhs);

    friend bool operator<=(const Date &lhs, const Date &rhs);

    friend bool operator==(const Date &lhs, const Date &rhs);

    friend ostream &operator<<(ostream &output, const Date &date);

private:
    int year;
    int month;
    int day;
};

Date ParseDate(istream &input);

void TestDateOutput();

void TestParseDate();




