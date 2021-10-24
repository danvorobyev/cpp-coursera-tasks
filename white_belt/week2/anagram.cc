#include <iostream>
#include <map>
#include <string>
using namespace std;

map<char, int> BuildCharCounters(string s) {
    map<char, int> result;
    for (char c : s) {
        result[c]++;
    }
    return result;
}

int main() {
    int n;

    cin >> n;
    string s1, s2;
    for (int i = 0; i < n; i++) {
        cin >> s1 >> s2;
        map<char, int> char_counter1 = BuildCharCounters(s1);
        map<char, int> char_counter2 = BuildCharCounters(s2);
        if (char_counter1 == char_counter2)
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }

    return 0;
}