#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

struct Operation {

};

int main() {
  int initial_number;
  cin >> initial_number;

  int number_of_operations;
  cin >> number_of_operations;

  deque<string> expression;
  expression.push_back(to_string(initial_number));

  for (int i = 0; i < number_of_operations; ++i) {
    char type = 0;
    int number = 0;
    cin >> type >> number;
    expression.push_front("(");
    expression.push_back(") ");
    expression.push_back(string(1, type));
    expression.push_back(" ");
    expression.push_back(to_string(number));
  }

  for (const string& s : expression) {
    cout << s;
  }
  cout << endl;

  return 0;
}
