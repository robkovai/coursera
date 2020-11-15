#include "database.h"

#include <sstream>

using namespace std;

void Database::Add(const Date& date, const string& event) {
    if (!this->data.count(date))
        this->data[date] = make_pair(Events(), EventIterators());

    auto& datePair = this->data[date];
    const auto itPair = datePair.first.insert(event);
    if (itPair.second)
        datePair.second.push_back(itPair.first);
}

void Database::Print(ostream& stream) const {
    for (const auto& date : this->data)
        for (const auto& event : date.second.second)
            stream << date.first << ' ' << *event << endl;
}

int Database::RemoveIf(Database::Predicate predicate) {
    int count = 0;
    for (auto itDate = this->data.begin(); itDate != this->data.end();) {
        const auto& date = itDate->first;
        auto& eventIterators = itDate->second.second;
        auto& events = itDate->second.first;

        for (auto it = eventIterators.begin(); it != eventIterators.end();) {
            if (predicate(date, **it)) {
                ++count;
                events.erase(*it);
                it = eventIterators.erase(it);
            } else
                ++it;
        }

        itDate = this->data[date].first.empty() ? this->data.erase(itDate) : ++itDate;
    }
    return count;
}

vector<string> Database::FindIf(Database::Predicate predicate) const {
    vector<string> result;
    for (const auto& date : this->data) {
        for (const auto& event : date.second.second)
            if (predicate(date.first, *event)) {
                ostringstream ss;
                ss << date.first << ' ' << *event;
                result.push_back(ss.str());
            }
    }
    return result;
}

string Database::Last(const Date& date) const {
    auto it = this->data.upper_bound(date);
    if (it == this->data.begin())
        throw invalid_argument("");
    --it;
    ostringstream ss;
    ss << it->first << ' ' << *it->second.second.back();
    return ss.str();
}
