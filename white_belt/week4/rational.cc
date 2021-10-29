#include <cmath>
#include <iostream>
using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else 
            b %= a;
    }
    return a + b;
}

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }
    Rational(int num, int denom) {
        int gcd_val = gcd(num, denom);
        numerator = num / gcd_val;
        denominator = denom / gcd_val;
        if (denominator < 0) { 
            denominator = -denominator;
            numerator = -numerator;
        }
    }

    int Numerator() const {
        return numerator;
    }
    int Denominator() const {
        return denominator;
    }

private:
    int numerator, denominator;
};