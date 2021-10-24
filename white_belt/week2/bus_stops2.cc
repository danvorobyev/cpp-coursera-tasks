#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;


int main() {
    int n;
    cin >> n;
    map<vector<string>, int> routes;
    int route_num = 1;
    for (int i = 0; i < n; i++) {
        int count;
        string stop;
        vector<string> stops;
        cin >> count;
        for (int j = 0; j < count; j++) {
            cin >> stop;
            stops.push_back(stop);
        }
        if (routes.count(stops) == 0) {
            routes[stops] = route_num;
            cout << "New bus " << route_num << endl;;
            route_num++;
        } else {
            cout << "Already exists for " << routes[stops] << endl;
        }
    }
    return 0;
}