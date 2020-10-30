#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstNames[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        lastNames[year] = last_name;
    }

    string GetFullName(int year) const {
        return GetFullName(year, false);
    }

    string GetFullNameWithHistory(int year) const {
        return GetFullName(year, true);
    }

private:
    using Names = map<int, string>;

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
        return GetName(year, names) + GetHistory(year, names);
    }

    string GetHistory(int year, const Names &names) const {
        if (names.empty())
            return string();
        vector<string> v;
        for (const auto &name : names) {
            if (name.first <= year) {
                if (!v.empty())
                    if (v.front() == name.second)
                        continue;
                v.insert(v.begin(), name.second);
            } else
                break;
        }
        if (!v.empty())
            v.erase(v.begin());
        
        if (v.empty())
            return string();

        string result = v.back();
        v.pop_back();
        for (const auto &name : v)
            result = name + ", " + result;

        return " (" + result + ")";
    }

    Names firstNames;
    Names lastNames;
};

int main() {
    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) 
        cout << person.GetFullNameWithHistory(year) << endl;
  
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) 
        cout << person.GetFullNameWithHistory(year) << endl;
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) 
        cout << person.GetFullNameWithHistory(year) << endl;
  
    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;
  
    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;
  
    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) 
        cout << person.GetFullNameWithHistory(year) << endl;
    
    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}