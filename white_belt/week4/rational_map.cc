#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
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

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.Denominator() == rhs.Denominator() 
           && lhs.Numerator() == rhs.Numerator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator()
        + rhs.Numerator() * lhs.Denominator();
    int denominator = lhs.Denominator() * rhs.Denominator();
    return Rational(numerator, denominator);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator()
        - rhs.Numerator() * lhs.Denominator();
    int denominator = lhs.Denominator() * rhs.Denominator();
    return Rational(numerator, denominator);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Numerator();
    int denominator = lhs.Denominator() * rhs.Denominator();
    return Rational(numerator, denominator);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int numerator = lhs.Numerator() * rhs.Denominator();
    int denominator = lhs.Denominator() * rhs.Numerator();
    return Rational(numerator, denominator);
}

istream& operator>>(istream& input, Rational& rational) {
    int numerator, denominator;
    char delimiter;
    if (input) {
        input >> numerator >> delimiter >> denominator;
        if (input && delimiter == '/')
            rational = Rational(numerator, denominator);
    }
    return input;
}

ostream& operator<<(ostream& output, const Rational& rational) {
    output << rational.Numerator() << "/" << rational.Denominator();
    return output;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (lhs - rhs).Numerator() < 0;
}