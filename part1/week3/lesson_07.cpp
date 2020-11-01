#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& first_name, const string& last_name, int year) {
        burn = year;
        ChangeFirstName(year, first_name);
        ChangeLastName(year, last_name);
    }

    void ChangeFirstName(int year, const string& first_name) {
        if (IsBurn(year))
            firstNames[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        if (IsBurn(year))
            lastNames[year] = last_name;
    }

    string GetFullName(int year) const {
        return IsBurn(year) ? GetFullName(year, false) : "No person";
    }

    string GetFullNameWithHistory(int year) const {
        return IsBurn(year) ? GetFullName(year, true) : "No person";
    }

private:
    using Names = map<int, string>;

    bool IsBurn(int year) const {
        return year >= burn;
    }

    string GetFullName(int year, bool withHistory) const {
        string firstName = withHistory ? GetFirstNameWithHistory(year) : GetFirstName(year);
        string lastName = withHistory ? GetLastNameWithHistory(year) : GetLastName(year);
        if (firstName.empty() && lastName.empty()) 
            return "Incognito";
        if (firstName.empty())
            return lastName + " with unknown first name";
        if (lastName.empty())
            return firstName + " with unknown last name";
        return firstName + " " + lastName;
    }

    string GetFirstName(int year) const {
        return GetName(year, firstNames);
    }

    string GetLastName(int year) const {
        return GetName(year, lastNames);
    }

    string GetFirstNameWithHistory(int year) const {
        return GetNameWithHistory(year, firstNames);
    }

    string GetLastNameWithHistory(int year) const {
        return GetNameWithHistory(year, lastNames);
    }

    string GetName(int year, const Names &names) const {
        if (names.empty())
            return string();
        auto it = names.upper_bound(year);
        if (it != names.begin())
            --it;
        return (*it).first > year ? string() : (*it).second;
    }

    string GetNameWithHistory(int year, const Names &names) const {
        return GetName(year, names) + JoinNames(GetHistory(year, names));
    }

    vector<string> GetHistory(int year, const Names &names) const {
        vector<string> result;
        for (const auto &name : names) 
            if (name.first <= year && (result.empty() || result.back() != name.second)) 
                result.push_back(name.second);

        if (!result.empty())
            result.pop_back();

        reverse(result.begin(), result.end());

        return result;
    }

    string JoinNames(const vector<string> &names) const {
        string result;

        if (names.empty())
            return result;

        for (int i = 0; i < names.size(); ++i) {
            if (i > 0)
                result += ", ";
            result += names.at(i);
        }

        return " (" + result + ")";
    }

    Names firstNames;
    Names lastNames;
    int burn;
};

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) 
        cout << person.GetFullNameWithHistory(year) << endl;
  
    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) 
        cout << person.GetFullNameWithHistory(year) << endl;

  return 0;
}