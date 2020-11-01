#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator, int denominator) {
        this->numerator = numerator / gcd(numerator, denominator);
        this->denominator = denominator / gcd(numerator, denominator);
        if (this->denominator < 0) {
            this->denominator = abs(this->denominator);
            this->numerator = -this->numerator;
        }
    }

    int Numerator() const {
        return this->numerator;
    }

    int Denominator() const {
        return this->denominator;
    }

    friend bool operator==(const Rational &lhs, const Rational &rhs) {
        int value = lhs.denominator * rhs.denominator;
        return lhs.numerator * (value / lhs.denominator) == rhs.numerator * (value / rhs.denominator);
    }

    friend Rational operator+(const Rational &lhs, const Rational &rhs) {
        int value = lhs.denominator * rhs.denominator;
        return Rational(lhs.numerator * (value / lhs.denominator) + rhs.numerator * (value / rhs.denominator), value);
    }

    friend Rational operator-(const Rational &lhs, const Rational &rhs) {
        int value = lhs.denominator * rhs.denominator;
        return Rational(lhs.numerator * (value / lhs.denominator) - rhs.numerator * (value / rhs.denominator), value);
    }

    friend Rational operator*(const Rational &lhs, const Rational &rhs) {
        return Rational(lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator);
    }

    friend Rational operator/(const Rational &lhs, const Rational &rhs) {
        return Rational(lhs.numerator, lhs.denominator) * Rational(rhs.denominator, rhs.numerator);
    }

private:
    int numerator = 0;
    int denominator = 1;
};

int main() {
        {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}