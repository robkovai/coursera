#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <set>

#include "test_runner.h"

using namespace std;

class Domains {
    set<string> bannedDomain;

    vector<string> ReadDomains(istream& input = cin) const {
        vector<string> result;
        size_t count;
        string domain;
        input >> count;
        result.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            input >> domain;
            result.push_back("." + move(domain));
        }
        return result;
    }

    bool IsBanned(const string& domain) const {
        if (this->bannedDomain.empty())
            return false;

        auto it = this->bannedDomain.lower_bound(domain);
        if (it != this->bannedDomain.end() && *it == domain)
            return true;

        if (auto pos = domain.find_first_of('.', 1); pos != string::npos) {
            if (this->IsBanned(domain.substr(pos, domain.size() - pos)))
                return true;
        }
        return false;
    }

public:
    Domains& ReadBannedDomains(istream& input = cin) {
        auto domains = this->ReadDomains(input);
        this->bannedDomain.insert(domains.begin(), domains.end());
        return *this;
    }

    const Domains& ReadDomainsToCheck(istream& input = cin, ostream& output = cout) const {
        auto domains = this->ReadDomains(input);
        for (const string& domain : domains)
            output << (this->IsBanned(domain) ? "Bad" : "Good") << '\n';
        return *this;
    }
};

void Test() {
    stringstream input("4\nya.ru\nmaps.me\nm.ya.ru\ncom\n"
                       "8\nya.ru\nya.com\nm.maps.me\nmoscow.m.ya.ru\nmaps.com\nmaps.ru\nya.ya\nmmaps.me\n");
    stringstream answer("Bad\nBad\nBad\nBad\nBad\nGood\nGood\nGood\n");
    stringstream output;
    Domains domains;
    domains.ReadBannedDomains(input).ReadDomainsToCheck(input, output);
    ASSERT_EQUAL(answer.str(), output.str());
}

void Test2() {
    stringstream input("8\nya.com\nspb.com\nm.com\nm.ya.com\nya.m.com\nya.ya.com\nyaya.com\nya.ru.com\n"
                       "8\ncom\nru.com\nspb.ru.com\nm.spb.com\ns.spb.com\nspb.m.com\nspb.yaya.com\nmoscow.ya.ru\n");
    stringstream answer("Good\nGood\nGood\nBad\nBad\nBad\nBad\nGood\n");
    stringstream output;
    Domains domains;
    domains.ReadBannedDomains(input).ReadDomainsToCheck(input, output);
    ASSERT_EQUAL(answer.str(), output.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    RUN_TEST(tr, Test2);

    Domains domains;
    domains.ReadBannedDomains().ReadDomainsToCheck();

    return 0;
}
