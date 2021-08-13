#include "test_runner.h"

#ifdef DEBUG
#include "solution.h"
#endif

void TestEmpty() {
    vector<Person> persons;
    ASSERT_EQUAL(ComputeMedianAge(persons.begin(), persons.end()), 0);
}

void TestMiddle() {
    vector<Person> persons = { Person{ 10, Gender::MALE, false }, Person{ 20, Gender::MALE, false }, Person { 30, Gender::MALE, false} };
    ASSERT_EQUAL(ComputeMedianAge(persons.begin(), persons.end()), 20);
}

void TestChangedGenderAndEmployed() {
    stringstream ss("1 10 1 0");
    ASSERT_EQUAL(ReadPersons(ss), vector<Person>({Person{10, Gender::MALE, false}}));
}

void TestEmployedMales() {
    ASSERT_EQUAL(ComputeStats(vector<Person>({{10, Gender::MALE, true}})).employed_males, 10);
}

void TestPrintOrder() {
    AgeStats stats = {1, 2, 3, 4, 5, 6, 7};
    ostringstream ss;
    PrintStats(stats, ss);
    ASSERT_EQUAL(ss.str(), "Median age = 1\n"
                 "Median age for females = 2\n"
                 "Median age for males = 3\n"
                 "Median age for employed females = 4\n"
                 "Median age for unemployed females = 5\n"
                 "Median age for employed males = 6\n"
                 "Median age for unemployed males = 7\n");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestMiddle);
    RUN_TEST(tr, TestChangedGenderAndEmployed);
    RUN_TEST(tr, TestEmployedMales);
    RUN_TEST(tr, TestPrintOrder);
}
