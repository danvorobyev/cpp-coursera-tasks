#pragma once

#include "date.h"
#include <map>
#include <set>
#include <vector>
#include <functional>

using namespace std;

class Database {
public:
    void Add(const Date &date, const string &event);

    vector<pair<Date, string>> FindIf(const function<bool(const Date &, const string &)> &func) const;

    int RemoveIf(const function<bool(const Date &, const string &)> &func);

    void Print(ostream &output) const;

    pair<Date, string> Last(const Date &date) const;

private:
    map<Date, vector<string>> ordered_events;
    map<Date, set<string>> unordered_events;
};

ostream &operator<<(ostream &output, const pair<Date, string> &date_event);

void TestDatabaseAddAndPrint();

void TestDatabaseFind();

void TestDatabaseRemove();

void TestDatabaseLast();
