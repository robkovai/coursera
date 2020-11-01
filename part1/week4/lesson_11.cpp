#include <iostream>
#include <numeric>
#include <cmath>
#include <sstream>
#include <set>
#include <vector>
#include <map>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int numerator, int denominator) {
        if (denominator == 0) 
            throw invalid_argument("0");
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
        if (rhs.numerator == 0)
            throw domain_error("0");
        return Rational(lhs.numerator, lhs.denominator) * Rational(rhs.denominator, rhs.numerator);
    }

    friend ostream& operator<<(ostream& stream, const Rational &rational) {
        stream << rational.numerator << '/' << rational.denominator;
        return stream;
    }

    friend istream& operator>>(istream& stream, Rational &rational) {
        int numerator, denominator;
        char delimeter;
        stream >> numerator >> delimeter >> denominator;
        if (!stream.fail() && delimeter == '/') {
            rational.numerator = numerator;
            rational.denominator = denominator;
        }
        return stream;
    }

    friend bool operator<(const Rational &lhs, const Rational &rhs) {
        int value = lhs.denominator * rhs.denominator;
        return lhs.numerator * (value / lhs.denominator) < rhs.numerator * (value / rhs.denominator);
    }

private:
    int numerator = 0;
    int denominator = 1;
};

int main() {
    try {
        Rational r1, r2;
        char operation;
        cin >> r1;
        cin.ignore(1);
        cin >> operation;
        cin.ignore(1);
        cin >> r2;
        switch (operation) {
            case '+': cout << r1 + r2 << endl; break;
            case '-': cout << r1 - r2 << endl; break;
            case '*': cout << r1 * r2 << endl; break;
            case '/': cout << r1 / r2 << endl; break;
        }
    } catch (invalid_argument &e) {
        cout << "Invalid argument" << endl;
    } catch (domain_error &e) {
        cout << "Division by zero" << endl;
    }
    return 0;
}