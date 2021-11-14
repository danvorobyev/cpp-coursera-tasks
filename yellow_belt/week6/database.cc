#include "database.h"


void Database::Add(const Date &date, const string &event) {
    if (unordered_events[date].find(event) == unordered_events[date].end()) {
        ordered_events[date].push_back(event);
        unordered_events[date].insert(event);
    }
}

ostream &operator<<(ostream &output, const pair<Date, string> &date_event) {
    return output << date_event.first << " " << date_event.second;
}

int Database::RemoveIf(const function<bool(const Date &, const string &)> &func) {
    int removed = 0;
    vector<Date> dates_to_erase;
    for (auto &item : ordered_events) {
        const auto &date = item.first;
        auto &events = item.second;

        auto it = stable_partition(events.begin(), events.end(),
                                   [&date, &func](const string &event) { return !func(date, event); });
        for (auto i = it; i != events.end(); i++) {
            unordered_events[date].erase(*i);
        }
        removed += events.end() - it;
        events.erase(it, events.end());

        if (events.empty()) {
            dates_to_erase.push_back(item.first);
        }
    }

    for (const auto &date : dates_to_erase) {
        ordered_events.erase(date);
        unordered_events.erase(date);
    }
    return removed;
}

pair<Date, string> Database::Last(const Date &date) const {
    auto first_greater = ordered_events.upper_bound(date);

    if (first_greater == ordered_events.begin())
        throw invalid_argument("");

    return make_pair(prev(first_greater)->first, prev(first_greater)->second.back());
}


void Database::Print(ostream &output) const {
    for (const auto&[date, events] : ordered_events) {
        for (const string &event : events) {
            output << date << " " << event << endl;
        }
    }
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date &, const string &)> &func) const {
    vector<pair<Date, string>> all_events;
    for (const auto &[date, events] : ordered_events) {
        for (const auto &event : events) {
            if (func(date, event)) {
                all_events.emplace_back(date, event);
            }
        }
    }
    return all_events;
}
