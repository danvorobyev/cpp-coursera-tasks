#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;

    cin >> s;

    int i = 0;
    int count = 0;
    for (i = 0; i < s.length(); i++) {
        if (s[i] == 'f')
            count++;
        if (count == 2)
            break;
    }
    
    if (count == 0 || count == 1)
        i = -2 + count;

    cout << i << endl;
    return 0;
}
    
