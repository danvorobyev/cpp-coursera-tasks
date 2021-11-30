#include "test_runner.h"

#include <iostream>
#include <list>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    list<int> player_positions;
    map<int, list<int>::iterator> player_pointers;

    for (int i = 0; i < n; ++i) {
        int curr_player_id, prev_player_id;

        cin >> curr_player_id >> prev_player_id;
        auto it = player_pointers.find(prev_player_id);
        if (it == player_pointers.end()) {
            player_positions.push_back(curr_player_id);
            player_pointers[curr_player_id] = prev(player_positions.end());
        } else {
            auto pos_it = it->second;
            player_positions.insert(pos_it, curr_player_id);
            player_pointers[curr_player_id] = prev(pos_it);
        }
    }

    for (auto p : player_positions) {
        cout << p << '\n';
    }

    return 0;
}