#include <iostream>
#include <numeric>

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

private:
    int numerator = 0;
    int denominator = 1;
};

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}