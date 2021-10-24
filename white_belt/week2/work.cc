#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const vector<int> MONTH_LENGTHS =
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MONTH_COUNT = MONTH_LENGTHS.size();

int month = 0;
vector<vector<string> > days_tasks(MONTH_LENGTHS[month]);

void add() {
    int day;
    string task;
    cin >> day >> task;
    day--;
    days_tasks[day].push_back(task);
}

void next() {
    const int old_month_length = MONTH_LENGTHS[month];
    month++;
    month %= 12;
    const int new_month_length = MONTH_LENGTHS[month];
    if (old_month_length > new_month_length) {
        vector<string>& last_day_tasks = days_tasks[new_month_length - 1];
        for (int day = new_month_length; day < old_month_length; day++) 
            last_day_tasks.insert(end(last_day_tasks), begin(days_tasks[day]), end(days_tasks[day]));
    }
    days_tasks.resize(new_month_length);
}

void dump() {
    int day;
    cin >> day;
    day--;
    cout << days_tasks[day].size() << " ";
    for (string task: days_tasks[day])
        cout << task << " ";
    cout << endl;
}


int main() {
    int n;
    cin >> n;
    string op;

    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "ADD")
            add();
        else if (op == "NEXT") 
            next();
        else
            dump();
    }
    return 0;
}