#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <numeric>

#include "test_runner.h"

using namespace std;

class Date {
public:
    explicit Date() = default;

    explicit Date(int year, int month, int day): year(year), month(month), day(day) {
        this->recalcEpochDays();
    }

    int getYear() const {
        return this->year;
    }

    int getMonth() const {
        return this->month;
    }

    int getDay() const {
        return this->day;
    }

    size_t getEpochDays() const {
        return this->epochDays;
    }

    friend istream& operator>>(istream& stream, Date& date) {
        stream >> date.year;
        stream.ignore();
        stream >> date.month;
        stream.ignore(1);
        stream >> date.day;
        date.recalcEpochDays();
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const Date& date) {
        stream << date.year << '-' << setw(2) << setfill('0') << date.month << '-' << setw(2) << setfill('0') << date.day;
        return stream;
    }

    static size_t getMaxDay() {
        return Date(2099, 12, 31).getEpochDays();
    }

private:
    static time_t getEpochDate(int year, int month, int day) {
        tm t;
        t.tm_sec   = 0;
        t.tm_min   = 0;
        t.tm_hour  = 0;
        t.tm_mday  = day;
        t.tm_mon   = month - 1;
        t.tm_year  = year - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

    void recalcEpochDays() {
        static const int SECONDS_IN_DAY = 60 * 60 * 24;
        static const int OFFSET_DAYS = Date::getEpochDate(2000, 1, 1) / SECONDS_IN_DAY;
        this->epochDays = Date::getEpochDate(this->year, this->month, this->day) / SECONDS_IN_DAY - OFFSET_DAYS;
    }

    int year = 0;
    int month = 0;
    int day = 0;
    size_t epochDays = 0;
};

class Budget {
public:
    Budget() {
        this->incomes.resize(Date::getMaxDay(), 0);
    }

    double computeIncome(Date from, Date to) const {
        return accumulate(this->getIncomeIterator(from), next(this->getIncomeIterator(to)), 0.0);
    }

    void earn(Date from, Date to, double value) {
        auto cost = value / (to.getEpochDays() - from.getEpochDays() + 1);
        for (size_t i = from.getEpochDays(); i < to.getEpochDays() + 1; ++i)
            this->incomes[i] += cost;
    }

    void payTax(Date from, Date to) {
        for (size_t i = from.getEpochDays(); i < to.getEpochDays() + 1; ++i)
            this->incomes[i] *= 0.87;
    }

private:
    vector<double>::const_iterator getIncomeIterator(const Date& date) const {
        return next(this->incomes.begin(), min(date.getEpochDays(), this->incomes.size()));
    }

    vector<double> incomes;
};

class BudgetReader {
public:
    explicit BudgetReader(Budget& budget): budget(budget) {}

    void read(istream& input, ostream& output) {
        size_t count;
        input >> count;
        for (size_t i = 0; i < count; ++i) {
            string command;
            Date from, to;
            input >> command >> from >> to;
            if (command == "Earn") {
                double value;
                input >> value;
                budget.earn(move(from), move(to), value);
            } else if (command == "ComputeIncome") {
                output << budget.computeIncome(move(from), move(to)) << '\n';
            } else if (command == "PayTax") {
                budget.payTax(move(from), move(to));
            }
        }
    }

private:
    Budget &budget;
};

void TestDate() {
    Date date(2010, 5, 21);
    ASSERT_EQUAL(date.getYear(), 2010);
    ASSERT_EQUAL(date.getMonth(), 5);
    ASSERT_EQUAL(date.getDay(), 21);
    ASSERT_EQUAL(Date(2000, 1, 1).getEpochDays(), 0);
    ASSERT_EQUAL(Date(2000, 2, 1).getEpochDays(), 31);
    ASSERT_EQUAL(Date(2001, 1, 1).getEpochDays(), 366);
}

void TestDateStreams() {
    stringstream ss("2010-05-21");
    stringstream result;
    Date date;
    ss >> date;
    result << date;
    ASSERT_EQUAL(ss.str() == result.str(), true);
}

void TestBudget() {
    Budget budget;
    budget.earn(Date(2000, 1, 2), Date(2000, 1, 6), 20);
    ASSERT_EQUAL(budget.computeIncome(Date(2000, 1, 1), Date(2001, 1, 1)), 20);

    budget.payTax(Date(2000, 1, 2), Date(2000, 1, 3));
    ASSERT_EQUAL(budget.computeIncome(Date(2000, 1, 1), Date(2001, 1, 1)), 18.96);

    budget.earn(Date(2000, 1, 3), Date(2000, 1, 3), 10);
    ASSERT_EQUAL(budget.computeIncome(Date(2000, 1, 1), Date(2001, 1, 1)), 28.96);

    budget.payTax(Date(2000, 1, 3), Date(2000, 1, 3));
    ASSERT_EQUAL(budget.computeIncome(Date(2000, 1, 1), Date(2001, 1, 1)), 27.2076);
}

void TestBudgetReader() {
    stringstream ss("8\n"
                    "Earn 2000-01-02 2000-01-06 20\n"
                    "ComputeIncome 2000-01-01 2001-01-01\n"
                    "PayTax 2000-01-02 2000-01-03\n"
                    "ComputeIncome 2000-01-01 2001-01-01\n"
                    "Earn 2000-01-03 2000-01-03 10\n"
                    "ComputeIncome 2000-01-01 2001-01-01\n"
                    "PayTax 2000-01-03 2000-01-03\n"
                    "ComputeIncome 2000-01-01 2001-01-01\n");
    stringstream answer("20\n"
                        "18.96\n"
                        "28.96\n"
                        "27.2076\n");
    stringstream result;
    Budget budget;
    BudgetReader(budget).read(ss, result);
    ASSERT_EQUAL(result.str(), answer.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestDate);
    RUN_TEST(tr, TestDateStreams);
    RUN_TEST(tr, TestBudget);
    RUN_TEST(tr, TestBudgetReader);

    Budget budget;
    cout.precision(25);
    BudgetReader(budget).read(cin, cout);

    return 0;
}
