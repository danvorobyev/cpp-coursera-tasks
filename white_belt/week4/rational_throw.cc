#include <iostream>
#include <exception>
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
        if (denom == 0)
            throw invalid_argument("invalid_argument");
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

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0)
        throw domain_error("domain_error");
    int numerator = lhs.Numerator() * rhs.Denominator();
    int denominator = lhs.Denominator() * rhs.Numerator();
    return Rational(numerator, denominator);
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}