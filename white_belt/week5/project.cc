#include <map>
#include <set>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Date {
public:
  Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month < 1 || new_month > 12) {
      throw runtime_error("Month value is invalid: " + to_string(new_month));
    } 
    month = new_month;
    if (new_day < 1 || new_day > 31) {
      throw runtime_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
private:
  int year;
  int month;
  int day;
};

Date ParseDateFromString(string line) {
  stringstream input(line);
  int year, month, day;
  char delim1, delim2;
  input >> year >> delim1 >> month >> delim2 >> day;
  if (!input || delim1 != '-' || delim2 != '-' || input.peek() != EOF) {
    throw runtime_error("Wrong date format: " + line);
  }
  return Date(year, month, day);
}

ostream& operator<<(ostream& output, const Date& date) {
  output   << setw(4) << setfill('0') << date.GetYear()
    << "-" << setw(2) << setfill('0') << date.GetMonth()
    << "-" << setw(2) << setfill('0') << date.GetDay();
  return output;
}

bool operator<(const Date& lhs, const Date& rhs) {
  if (lhs.GetYear() != rhs.GetYear())
    return lhs.GetYear() < rhs.GetYear();
  else if (lhs.GetMonth() != rhs.GetMonth())
    return lhs.GetMonth() < rhs.GetMonth();
  else 
    return lhs.GetDay() < rhs.GetDay();
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    events[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
    return events[date].erase(event);
  }
  int  DeleteDate(const Date& date) {
    int N = events[date].size();
    events.erase(date);
    return N;
  }

  void Find(const Date& date) const {
    if (events.find(date) != events.end()) {
      for (const string& event : events.at(date)) {
        cout << event << endl;
      }
    }
  };
  
  void Print() const {
    for (const auto& item : events) {
      for (const string& event : item.second) {
        cout << item.first << " " << event << endl;
      }
    }
  }

private:
  map<Date, set<string> > events;
};

class DBrunner {
public:
  void query_processing() {
    string line; 
    while(getline(cin, line)) {
      if (line.empty())
        continue;

      stringstream input(line);

      string operation;
      input >> operation;

      exec_operation(operation, input);
    }
  }
private:
  Database db;

  void exec_operation(const string& operation, stringstream& input) {
    if (operation == "Add") {
      exec_add(input);
    } else if (operation == "Del"){
      exec_del(input);
    } else if (operation == "Find") {
      exec_find(input);
    } else if (operation == "Print") {
      exec_print();
    } else {
      ostringstream oss;
      oss << "Unknown command: " << operation; 
      throw runtime_error(oss.str());
    }
  }

  void exec_add(stringstream& input) {
    string date_line, event;

    input >> date_line >> event;

    Date date = ParseDateFromString(date_line);

    getline(input, event);

    db.AddEvent(date, event);
  }

  void exec_del(stringstream& input) {
    string date_line, event;

    input >> date_line;

    Date date = ParseDateFromString(date_line);

    if (input.peek() != EOF) {
      input >> event;
      if (db.DeleteEvent(date,event))
        cout << "Deleted successfully" << endl;
      else
        cout << "Event not found" << endl;
    } else {
      cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
    }
  }

  void exec_find(stringstream& input) {
    string date_line;

    input >> date_line;

    Date date = ParseDateFromString(date_line);

    db.Find(date);
  }

  void exec_print() {
    db.Print();
  }
};

int main() {
  string line;
  DBrunner runner;
  try {
    runner.query_processing();
  } catch(const runtime_error& err) {
    cout << err.what() << endl;
  }
  return 0;
}