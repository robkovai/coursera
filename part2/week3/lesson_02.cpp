#include "phone_number.h"

#include <algorithm>
#include <stdexcept>

PhoneNumber::PhoneNumber(const string &international_number) {
    if (international_number.empty())
        throw invalid_argument("empty");

    if (international_number[0] != '+')
        throw invalid_argument("first charachter is not '+'");

    if (count(international_number.begin(), international_number.end(), '-') < 2)
        throw invalid_argument("invalid format");

    size_t begin_pos = 1;
    size_t end_pos = international_number.find('-') - 1;

    country_code_ = international_number.substr(begin_pos, end_pos);

    begin_pos = end_pos + 2;
    end_pos = international_number.find('-', begin_pos);

    city_code_ = international_number.substr(begin_pos, end_pos - begin_pos);
    local_number_ = international_number.substr(end_pos + 1, international_number.size());

    if (country_code_.empty() || city_code_.empty() || local_number_.empty())
        throw invalid_argument("empty code");
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}