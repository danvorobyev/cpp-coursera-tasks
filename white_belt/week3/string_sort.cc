#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);
    for (string& str : strings)
        cin >> str;

    sort(begin(strings), end(strings), [](const string& str1, const string& str2) {
        return lexicographical_compare(
            begin(str1), end(str1),
            begin(str2), end(str2),
            [](const char char1, const char char2) {
                return tolower(char1) < tolower(char2);
            });
    });

    for (const string& str : strings)
        cout << str << " ";
    cout << endl;
    return 0;
}
