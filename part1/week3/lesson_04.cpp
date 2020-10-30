#include <iostream>
#include <map>
#include <algorithm>
#include <string>

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

int main() {
    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) 
        cout << person.GetFullName(year) << endl;

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
        cout << person.GetFullName(year) << endl;
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) 
        cout << person.GetFullName(year) << endl;

    return 0;
}