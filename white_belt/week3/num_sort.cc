#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int& num : nums)
        cin >> num;

    sort(begin(nums), end(nums), [](int num1, int num2) {
        return abs(num1) < abs(num2);
    });

    for (const int num : nums)
        cout << num << " ";
    cout << endl;
    return 0;
}
