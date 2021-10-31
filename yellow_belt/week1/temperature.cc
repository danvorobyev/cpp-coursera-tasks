#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> temps(N);
    int64_t sum = 0;    

    for (int& temp : temps) {
        cin >> temp;
        sum += temp;
    }

    int average = sum / N; 

    vector<int> high_temp_idxs;

    for (int i = 0; i < N; i++) {
        if (temps[i] > average) {
            high_temp_idxs.push_back(i);
        }
    }
    
    cout << high_temp_idxs.size() << endl;

    for (int idx : high_temp_idxs) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;      
}
