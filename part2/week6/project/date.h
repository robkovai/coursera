#pragma once

#include <iostream>

class Date {
public:
    Date() = default;
    Date(int year, int month, int day);

    int GetYear() const;
    void SetYear(int year);

    int GetMonth() const;
    void SetMonth(int month);

    int GetDay() const;
    void SetDay(int day);

    void SetDate(int year, int month, int day);

    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);

    friend std::istream& operator>>(std::istream& stream, Date& date);
    friend std::ostream& operator<<(std::ostream& stream, const Date& date);

private:
    int year = 0;
    int month = 0;
    int day = 0;
};

Date ParseDate(std::istream& is);
