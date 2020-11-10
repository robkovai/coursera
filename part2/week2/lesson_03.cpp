#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstNames[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        lastNames[year] = last_name;
    }

    string GetFullName(int year) const {
        string firstName = GetFirstName(year);
        string lastName = GetLastName(year);
        if (firstName.empty() && lastName.empty()) 
            return "Incognito";
        if (firstName.empty())
            return lastName + " with unknown first name";
        if (lastName.empty())
            return firstName + " with unknown last name";
        return firstName + " " + lastName;
    }

private:
    using Names = map<int, string>;

    string GetFirstName(int year) const {
        return GetName(year, firstNames);
    }

    string GetLastName(int year) const {
        return GetName(year, lastNames);
    }

    string GetName(int year, const Names &names) const {
        if (names.empty())
            return string();
        auto it = --names.upper_bound(year);
        return (*it).first > year ? string() : (*it).second;
    }

    Names firstNames;
    Names lastNames;
};
#endif

void TestPerson() {
    {
        Person person;
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        AssertEqual(person.GetFullName(1960), "Incognito");
        AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
        AssertEqual(person.GetFullName(1990), "Polina Sergeeva");

        person.ChangeFirstName(1970, "Appolinaria");
        AssertEqual(person.GetFullName(1969), "Polina Sergeeva");
        AssertEqual(person.GetFullName(1970), "Appolinaria Sergeeva");

        person.ChangeLastName(1968, "Volkova");
        AssertEqual(person.GetFullName(1969), "Polina Volkova");
        AssertEqual(person.GetFullName(1970), "Appolinaria Volkova");
    }
    {
        Person person;
        person.ChangeLastName(1967, "Sergeeva");
        AssertEqual(person.GetFullName(1960), "Incognito");
        AssertEqual(person.GetFullName(1990), "Sergeeva with unknown first name");
    }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPerson, "TestPerson");
  return 0;
}
