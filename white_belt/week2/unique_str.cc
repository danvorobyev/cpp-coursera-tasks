#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    int N;
    cin >> N;
    set<string> strings;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        strings.insert(s);
    }
    cout << strings.size() << endl;
    return 0;
}