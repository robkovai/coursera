#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef DEBUG

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) 
        return 0;

    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(begin(range_copy), middle, end(range_copy), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
        });
  return middle->age;
}

#endif

int GetAgeAll(vector<Person>& persons) {
    return ComputeMedianAge(persons.begin(), persons.end());
}

int GetAgeForGender(vector<Person>& persons, Gender gender) {
    auto it = partition(persons.begin(), persons.end(), [&gender](const auto& value) {
        return value.gender == gender;
    });
    return ComputeMedianAge(persons.begin(), it);
}

int GetAgeForGenderAndEmployed(vector<Person>& persons, Gender gender, bool is_employed) {
    auto it = partition(persons.begin(), persons.end(), [&gender, &is_employed](const auto& value) {
        return value.gender == gender && value.is_employed == is_employed;
    });
    return ComputeMedianAge(persons.begin(), it);
}

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << GetAgeAll(persons) << endl;
    cout << "Median age for females = " << GetAgeForGender(persons, Gender::FEMALE) << endl;
    cout << "Median age for males = " << GetAgeForGender(persons, Gender::MALE) << endl;
    cout << "Median age for employed females = " << GetAgeForGenderAndEmployed(persons, Gender::FEMALE, true) << endl;
    cout << "Median age for unemployed females = " << GetAgeForGenderAndEmployed(persons, Gender::FEMALE, false) << endl;
    cout << "Median age for employed males = " << GetAgeForGenderAndEmployed(persons, Gender::MALE, true) << endl;
    cout << "Median age for unemployed males = " << GetAgeForGenderAndEmployed(persons, Gender::MALE, false) << endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
