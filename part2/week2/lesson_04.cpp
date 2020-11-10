#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#ifdef DEBUG
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

private:
    int numerator = 0;
    int denominator = 1;
};
#endif

void TestRationalDefaultConstructor() {
    Rational rational;
    AssertEqual(rational.Numerator(), 0);
    AssertEqual(rational.Denominator(), 1);
}

void TestRationalWithParameters() {
    Rational rational(6, 9);
    AssertEqual(rational.Numerator(), 2);
    AssertEqual(rational.Denominator(), 3);
}

void TestRationalNegative() {
    {
        Rational rational(-2, 5);
        AssertEqual(rational.Numerator(), -2);
        AssertEqual(rational.Denominator(), 5);
    }
    {
        Rational rational(2, -5);
        AssertEqual(rational.Numerator(), -2);
        AssertEqual(rational.Denominator(), 5);
    }
}

void TestRationalPositive() {
    {
        Rational rational(2, 5);
        AssertEqual(rational.Numerator(), 2);
        AssertEqual(rational.Denominator(), 5);
    }
    {
        Rational rational(-2, -5);
        AssertEqual(rational.Numerator(), 2);
        AssertEqual(rational.Denominator(), 5);
    }
}

void TestRationalNumeratorZero() {
    Rational rational(0, 5);
    AssertEqual(rational.Numerator(), 0);
    AssertEqual(rational.Denominator(), 1);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestRationalDefaultConstructor, "TestRationalDefaultConstructor");
    runner.RunTest(TestRationalWithParameters, "TestRationalWithParameters");
    runner.RunTest(TestRationalNegative, "TestRationalNegative");
    runner.RunTest(TestRationalPositive, "TestRationalPositive");
    runner.RunTest(TestRationalNumeratorZero, "TestRationalNumeratorZero");
    return 0;
}