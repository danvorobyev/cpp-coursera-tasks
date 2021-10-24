#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;


int main() {
    int n;
    cin >> n;
    map<set<string>, int> routes;
    for (int i = 0; i < n; i++) {
        int count;
        string stop;
        set<string> stops;
        cin >> count;
        for (int j = 0; j < count; j++) {
            cin >> stop;
            stops.insert(stop);
        }
        if (routes.count(stops) == 0) {
            routes[stops] = routes.size() + 1;
            cout << "New bus " << routes[stops] << endl;;
        } else {
            cout << "Already exists for " << routes[stops] << endl;
        }
    }
    return 0;
}