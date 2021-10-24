#include <iostream>
#include <cassert>
using namespace std;

bool is_even(int number) {
    return number % 2 == 0;
}

int main() {
    int a, b;

    cin >> a >> b;

    assert(a <= b);
    assert(a >= 1);
    assert(b <= 30000);

    for (int num = a; num <= b; num++)
        if (is_even(num))
            cout << num << endl;

    return 0;
}
