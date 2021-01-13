#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "test_runner.h"

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = size_t;

    Id Add(T object) {
        const Id id = objects.size();
        objects.push_back(PriorityT(move(object)));
        priorities.insert({0, id});
        return id;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        while (range_begin != range_end)
            *ids_begin++ = Add(move(*range_begin++));
    }

    bool IsValid(Id id) const {
        return id < objects.size() && objects.at(id).priority != PriorityNotValid;
    }

    const T& Get(Id id) const {
        return objects[id].object;
    }

    void Promote(Id id) {
        auto& priority = objects[id].priority;
        priorities.erase({ priority, id });
        priorities.insert({ ++priority, id });
    }

    pair<const T&, int> GetMax() const {
        const auto& object = objects[prev(priorities.end())->second];
        return { object.object, object.priority };
    }

    pair<T, int> PopMax() {
        auto it = prev(priorities.end());
        auto& object = objects[it->second];
        priorities.erase(it);
        auto priority = object.priority;
        object.priority = PriorityNotValid;
        return { move(object.object), priority };
    }

private:
    struct PriorityT {
        explicit PriorityT(T object): object(move(object)) {}
        T object;
        int priority = 0;
    };

    const int PriorityNotValid = -1;

    vector<PriorityT> objects;
    set<pair<int, Id>> priorities;
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
        strings.Promote(red_id);

    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
