#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <memory>
#include <set>

#include "test_runner.h"

using namespace std;

struct Person {
    string name;
    int age, income;
    bool is_male;
};

class Database {
    vector<Person> persons;
    optional<string> popularNameMale, popularNameFemale;
    vector<int> wealthies;

    void ReadPeople(istream& input) {
        int count;
        input >> count;

        this->persons.resize(count);
        for (auto& p : this->persons) {
            char gender;
            input >> p.name >> p.age >> p.income >> gender;
            p.is_male = gender == 'M';
        }
        sort(persons.begin(), persons.end(), [](const auto& lhs, const auto& rhs) {
            return lhs.age < rhs.age;
        });
    }

    void FindPopularNames() {
        map<string, size_t> males;
        map<string, size_t> females;

        for (const auto& p : this->persons) {
            auto& c = p.is_male ? males : females;
            c[p.name]++;
        }

        const auto Max = [](const auto &lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        };

        auto maxMale = max_element(males.begin(), males.end(), Max);
        if (maxMale != males.end())
            this->popularNameMale = maxMale->first;

        auto maxFemale = max_element(females.begin(), females.end(), Max);
        if (maxFemale != females.end())
            this->popularNameFemale = maxFemale->first;
    }

    void CalcWealthies() {
        multiset<int, std::greater<int>> incomes;
        for (const auto& p : this->persons)
            incomes.insert(p.income);

        this->wealthies.resize(this->persons.size());
        int i = 0;
        for (const auto& income : incomes) {
            if (i == 0)
                this->wealthies[i] = income;
            else
                this->wealthies[i] = this->wealthies[i - 1] + income;
            ++i;
        }
    }

    string ReadCommandAge(istream& input) const {
        int adult_age;
        input >> adult_age;
        auto count = distance(lower_bound(persons.begin(), persons.end(), adult_age, [](const auto& lhs, int age) {
            return lhs.age < age;
        }), persons.end());
        return "There are " + to_string(count) + " adult people for maturity age " + to_string(adult_age) + '\n';
    }

    string ReadCommandWealthy(istream& input) const {
        int count;
        input >> count;
        return "Top-" + to_string(count) + " people have total income " + to_string(this->wealthies[count - 1]) + '\n';
    }

    string ReadCommandPopularName(istream& input) const {
        char gender;
        input >> gender;
        const auto &name = gender == 'M' ? this->popularNameMale : this->popularNameFemale;
        ostringstream result;
        if (name)
            result << "Most popular name among people of gender " << gender << " is " << *name << '\n';
        else
            result << "No people of gender " << gender << '\n';
        return result.str();
    }

public:
    explicit Database(istream &input) {
        this->ReadPeople(input);
        this->FindPopularNames();
        this->CalcWealthies();
    }

    void ReadCommands(istream& input, ostream& output) const {
        for (string command; input >> command; ) {
            if (command == "AGE")
                output << this->ReadCommandAge(input);
            else if (command == "WEALTHY")
                output << this->ReadCommandWealthy(input);
            else if (command == "POPULAR_NAME")
                output << this->ReadCommandPopularName(input);
        }
    }
};

void Test() {
    istringstream data("11"
                       "Ivan 25 1000 M"
                       "Olga 30 623 W"
                       "Sergey 24 825 M"
                       "Maria 42 1254 W"
                       "Mikhail 15 215 M"
                       "Oleg 18 230 M"
                       "Denis 53 8965 M"
                       "Maxim 37 9050 M"
                       "Ivan 47 19050 M"
                       "Ivan 17 50 M"
                       "Olga 23 550 W");
    const Database db(data);

    const auto Query = [&db](string query, string expected) {
        istringstream stream(query);
        ostringstream result;
        db.ReadCommands(stream, result);
        ASSERT_EQUAL(result.str(), expected);
    };

    Query("AGE 18",         "There are 9 adult people for maturity age 18\n");
    Query("AGE 25",         "There are 6 adult people for maturity age 25\n");
    Query("WEALTHY 5",      "Top-5 people have total income 39319\n");
    Query("POPULAR_NAME M", "Most popular name among people of gender M is Ivan\n");
    Query("POPULAR_NAME W", "Most popular name among people of gender W is Olga\n");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);

    const Database db(cin);
    db.ReadCommands(cin, cout);

    return 0;
}
