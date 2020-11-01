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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}