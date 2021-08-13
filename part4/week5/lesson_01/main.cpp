#include "test_runner.h"
#include "common.h" // Закомментировать перед отправкой

#include <iostream>
#include <map>

using namespace std;

template<typename Condition>
int ComputeMedian(std::vector<Person> persons, Condition condition) {
    return ComputeMedianAge(persons.begin(), std::partition(persons.begin(), persons.end(), condition));
}

void PrintMedianAge(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age = " << ComputeMedian(persons, [](const auto&) {
        return true;
    }) << "\n";
}

void PrintMedianAgeForFemales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for females = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::FEMALE;
    }) << "\n";
}

void PrintMedianAgeForMales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for males = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::MALE;
    }) << "\n";
}

void PrintMedianAgeForEmployedFemales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for employed females = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::FEMALE && p.is_employed;
    }) << "\n";
}

void PrintMedianAgeForUnmployedFemales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for unemployed females = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::FEMALE && !p.is_employed;
    }) << "\n";
}

void PrintMedianAgeForEmployedMales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for employed males = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::MALE && p.is_employed;
    }) << "\n";
}

void PrintMedianAgeForUnmployedMales(std::vector<Person> persons, std::ostream& stream = std::cout) {
    stream << "Median age for unemployed males = " << ComputeMedian(persons, [](const auto& p) {
        return p.gender == Gender::MALE && !p.is_employed;
    }) << "\n";
}

void PrintStats(std::vector<Person> persons, std::ostream& stream = std::cout) {
    PrintMedianAge(persons, stream);
    PrintMedianAgeForFemales(persons, stream);
    PrintMedianAgeForMales(persons, stream);
    PrintMedianAgeForEmployedFemales(persons, stream);
    PrintMedianAgeForUnmployedFemales(persons, stream);
    PrintMedianAgeForEmployedMales(persons, stream);
    PrintMedianAgeForUnmployedMales(persons, stream);
}

void Test() {
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
    const auto answer = "Median age = 40\n"
                        "Median age for females = 40\n"
                        "Median age for males = 55\n"
                        "Median age for employed females = 40\n"
                        "Median age for unemployed females = 80\n"
                        "Median age for employed males = 55\n"
                        "Median age for unemployed males = 78\n";

    std::stringstream result;
    PrintStats(persons, result);

    ASSERT_EQUAL(answer, result.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}
