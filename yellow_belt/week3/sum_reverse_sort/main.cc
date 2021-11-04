#include "sum_reverse_sort.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << Sum(1, 2) << endl;

    vector<int> v = {4, 3, 1, 2};
    Sort(v);

    for (auto i : v)
        cout << i << endl;

    cout << Reverse("test") << endl;
    return 0;
}