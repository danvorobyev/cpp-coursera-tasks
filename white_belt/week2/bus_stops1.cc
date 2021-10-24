#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, vector<string> > stops_for_buses;
map<string, vector<string> > buses_for_stops;

void new_bus() {
    string bus, stop;
    int stop_count;
    cin >> bus >> stop_count;
    for (int i = 0; i < stop_count; i++) {
        cin >> stop;
        buses_for_stops[stop].push_back(bus);
        stops_for_buses[bus].push_back(stop);
    }
}

void buses_for_stop() {
    string stop;
    cin >> stop;
    if (buses_for_stops.count(stop) == 0) {
        cout << "No stop" << endl;
        return;
    }
    for (string bus : buses_for_stops[stop])
        cout << bus << " ";
    cout << endl;
}

void stops_for_bus() {
    string bus;
    cin >> bus;
    if (stops_for_buses.count(bus) == 0) {
        cout << "No bus" << endl;
        return;
    }
    for (string stop : stops_for_buses[bus]) {
        cout << "Stop " << stop << ": ";
        if (buses_for_stops[stop].size() == 1) {
            cout << "no interchange" << endl;
        } else {
            for (string stop_bus : buses_for_stops[stop]) {
                if (stop_bus != bus)
                    cout << stop_bus << " ";
            }
            cout << endl; 
        }
    }
}

void all_buses() {
    if (stops_for_buses.empty()) {
        cout << "No buses" << endl;
        return;
    }
    for (auto item : stops_for_buses) {
        cout << "Bus " << item.first << ": ";
        for (string stop : item.second) 
            cout << stop << " ";
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    string op;

    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "NEW_BUS")
            new_bus();
        else if (op == "BUSES_FOR_STOP") 
            buses_for_stop();
        else if (op == "STOPS_FOR_BUS")
            stops_for_bus();
        else 
            all_buses();
    }
    return 0;
}