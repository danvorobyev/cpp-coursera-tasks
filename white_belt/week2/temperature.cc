#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> temperatures(n);

    int sum = 0;
    for (int& temp : temperatures) {
        cin >> temp;
        sum += temp;
    }
    double average = sum / n;

    int idx = 0;
    vector<int> high_temperatures;
    for (int temp : temperatures) {
        if (temp > average)
            high_temperatures.push_back(idx);
        idx++;
    }

    cout << high_temperatures.size() << endl;

    for (int temp : high_temperatures)
        cout << temp << " ";
    cout << endl;

    return 0;
}