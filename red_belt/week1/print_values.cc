#include "test_runner.h"

#include <iostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
  if (true)
    PRINT_VALUES(cout, 1, 3);
else 
    PRINT_VALUES(cout, 1, 3);
  return 0;
}
