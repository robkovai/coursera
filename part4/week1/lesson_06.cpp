#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

struct Record {
    using Pointer = shared_ptr<Record>;

    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

class Database {
public:
    bool Put(const Record& record) {
        auto value = make_shared<Record>(record);
        auto result = this->records.insert({ record.id, Data(value) });
        if (!result.second)
            return false;

        result.first->second.userIt = this->recordsByUser.insert({ record.user, value });
        result.first->second.timestampIt = this->recordsByTimestamp.insert({ record.timestamp, value });
        result.first->second.karmaIt = this->recordsByKarma.insert({ record.karma, value });

        return true;
    }

    const Record* GetById(const string& id) const {
        auto it = this->records.find(id);
        return it == this->records.end() ? nullptr : it->second.record.get();
    }

    bool Erase(const string& id) {
        auto it = this->records.find(id);
        if (it == this->records.end())
            return false;

        this->recordsByUser.erase(it->second.userIt);
        this->recordsByTimestamp.erase(it->second.timestampIt);
        this->recordsByKarma.erase(it->second.karmaIt);
        this->records.erase(it);

        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto begin = this->recordsByTimestamp.lower_bound(low);
        auto end = this->recordsByTimestamp.upper_bound(high);
        for (auto it = begin; it != end; ++it)
            if (!callback(*it->second.get()))
                return;
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto begin = this->recordsByKarma.lower_bound(low);
        auto end = this->recordsByKarma.upper_bound(high);
        for (auto it = begin; it != end; ++it)
            if (!callback(*it->second.get()))
                return;
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto pair = this->recordsByUser.equal_range(user);
        for (auto it = pair.first; it != pair.second; ++it)
            if (!callback(*it->second.get()))
                return;
    }

private:
    template<typename T>
    using Index = multimap<T, Record::Pointer>;

    struct Data {
        Data(Record::Pointer value): record(value) {}
        Record::Pointer record;
        Index<int>::iterator timestampIt;
        Index<int>::iterator karmaIt;
        Index<string>::iterator userIt;
    };

    unordered_map<string, Data> records;
    Index<int> recordsByTimestamp;
    Index<int> recordsByKarma;
    Index<string> recordsByUser;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
