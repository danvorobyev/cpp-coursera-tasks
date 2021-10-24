#include <iostream>
#include <cassert>
using namespace std;

int gcd(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else 
            b %= a;
    }
    return a + b;
}

int main() {
    int a, b;

    cin >> a >> b;

    assert(a > 0);
    assert(b > 0);

    cout << gcd(a, b) << endl;
    return 0;
}
