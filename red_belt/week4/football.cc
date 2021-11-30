#include "test_runner.h"

#include <iostream>
#include <list>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    list<int> row;
    vector<list<int>::iterator> positions(n + 1, row.end())

    for (int i = 0; i < n; ++i) {
        int curr_athlete_id, next_athlete_id;

        cin >> curr_athlete_id >> next_athlete_id;
        row.insert(positions[next_athlete_id], curr_athlete_id);
    }

    for (auto p : player_positions) {
        cout << p << '\n';
    }

    return 0;
}