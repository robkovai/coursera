#include "date.h"

#include <sstream>
#include <iomanip>

using namespace std;

Date ParseDate(istream& is) {
    Date date;
    is >> date;
    return date;
}

Date::Date(int year, int month, int day) {
    this->SetDate(year, month, day);
}

int Date::GetYear() const {
    return this->year;
}

void Date::SetYear(int year) {
    this->year = year;
}

int Date::GetMonth() const {
    return this->month;
}

void Date::SetMonth(int month) {
    if (month > 12 || month < 1)
        throw invalid_argument("Month value is invalid: " + to_string(month));
    this->month = month;
}

int Date::GetDay() const {
    return this->day;
}

void Date::SetDay(int day) {
    if (day > 31 || day < 1)
        throw invalid_argument("Day value is invalid: " + to_string(day));
    this->day = day;
}

void Date::SetDate(int year, int month, int day) {
    this->SetYear(year);
    this->SetMonth(month);
    this->SetDay(day);
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setfill('0') << setw(4) << date.year << '-' << setw(2) << date.month << '-' << setw(2) << date.day;
    return stream;
}

istream &operator>>(istream &stream, Date &date) {
    string date_string;
    stream >> date_string;
    stringstream ss(date_string);
    int year, month, day;
    char delimeter1, delimeter2;
    ss >> year >> delimeter1 >> month >> delimeter2 >> day;
    if (ss.fail() || !ss.eof() || delimeter1 != '-' || delimeter2 != '-')
        throw invalid_argument("Wrong date format: " + date_string);
    date.SetDate(year, month, day);
    return stream;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs.year == rhs.year ? (lhs.month == rhs.month ? lhs.day < rhs.day : lhs.month < rhs.month) : lhs.year < rhs.year;
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date &lhs, const Date &rhs) {
    return rhs < lhs;
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return rhs < lhs || rhs == lhs;
}

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}
