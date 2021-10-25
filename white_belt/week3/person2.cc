#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

string FindNameByYear(int year, const map<int, string>& names) {
    string name;
    for (const auto& item : names) {
        if (item.first <= year)
            name = item.second;
        else 
            break;
    }
    return name;
}

vector<string> GetHistoryByYear(int year, const map<int, string>& names) {
    vector<string> history_names;
    string name;
    for (const auto& item : names) {
        if (item.first <= year && name != item.second) {
            name = item.second;
            history_names.push_back(name);
        }
        else  {
            break;
        }
    }
    return history_names;
}


string FindNameHistoryByYear(int year, const map<int, string>& names) {
    vector<string> history_names = GetHistoryByYear(year, names);

    if (history_names.empty())
        return "";

    string history = history_names[history_names.size() - 1];

    if (history_names.size() > 1) {
        history += " (" + history_names[history_names.size() - 2];
        for (int i = history_names.size() - 3; i >= 0; i--) {
            history += ", " + history_names[i];
        }
        history += ")" ;
    }
    return history;
}

string BuildFullName(const string& first_name, const string& last_name) {
    if (first_name.empty() && last_name.empty())
        return "Incognito";
    if (first_name.empty())
        return last_name + " with unknown first name";
    if (last_name.empty())
        return first_name + " with unknown last name";
    return first_name + " " + last_name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) const {
        const string first_name = FindNameByYear(year, first_names);
        const string last_name = FindNameByYear(year, last_names);
        return BuildFullName(first_name, last_name);
    }
    string GetFullNameWithHistory(int year) const {
        const string first_name_history = FindNameHistoryByYear(year, first_names);
        const string last_name_history = FindNameHistoryByYear(year, last_names);
        return BuildFullName(first_name_history, last_name_history);
    }
private:
    map<int, string> first_names;
    map<int, string> last_names;
};