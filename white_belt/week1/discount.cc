#include <iostream>
using namespace std;

double get_discount(double n, double x) {
    return n * x / 100;
}

int main() {
    double n, a, b, x, y;

    cin >> n >> a >> b >> x >> y;

    if (n > b)
        n -= get_discount(n, y);
    else if (n > a)
        n -= get_discount(n, x);

    cout << n << endl;

    return 0;
}
