#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include <functional>

#include "date.h"

class Database {
public:
    using Predicate = std::function<bool(const Date& date, const std::string& event)>;
    using Events = std::set<std::string>;
    using EventIterator = typename Events::iterator;
    using EventIterators = std::vector<EventIterator>;

    void Add(const Date& date, const std::string& event);
    void Print(std::ostream& stream) const;
    int RemoveIf(Predicate predicate);
    std::vector<std::string> FindIf(Predicate predicate) const;
    std::string Last(const Date& date) const;

private:
    std::map<Date, std::pair<Events, EventIterators>> data;
};
