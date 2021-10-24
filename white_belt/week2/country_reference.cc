#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, string> country_capitals;

void change_capital() {
    string country, new_capital;
    cin >> country >> new_capital;
    if (country_capitals.count(country) == 0) {
        cout << "Introduce new country " << country 
             <<" with capital " << new_capital << endl;
        country_capitals[country] = new_capital;
        return;
    }
    if (country_capitals[country] == new_capital) {
        cout << "Country " << country 
             << " hasn't changed its capital" << endl;
        return;
    }
    cout << "Country " << country 
         <<" has changed its capital from " 
         << country_capitals[country] << " to " << new_capital << endl;
    country_capitals[country] = new_capital;
}

void rename() {
    string old_country_name, new_country_name;
    cin >> old_country_name >> new_country_name;
    if (old_country_name == new_country_name 
        || country_capitals.count(old_country_name) == 0 
        || country_capitals.count(new_country_name) == 1) {
        cout << "Incorrect rename, skip" << endl;
        return;
    }
    country_capitals[new_country_name] = country_capitals[old_country_name];
    country_capitals.erase(old_country_name);
    cout << "Country " << old_country_name 
         << " with capital " << country_capitals[new_country_name] 
         << " has been renamed to " << new_country_name << endl;
}

void about() {
    string country;
    cin >> country;
    if (country_capitals.count(country) == 0) {
        cout << "Country " << country 
             << " doesn't exist" << endl;
        return;
    }
    cout << "Country " << country 
         << " has capital " << country_capitals[country] << endl;
}

void dump() {
    if (country_capitals.empty()) {
        cout << "There are no countries in the world" << endl;
        return;
    }
    for (auto item : country_capitals) {
        cout << item.first << "/" << item.second << " "; 
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    string op;

    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "CHANGE_CAPITAL")
            change_capital();
        else if (op == "RENAME") 
            rename();
        else if (op == "ABOUT")
            about();
        else 
            dump();
    }
    return 0;
}