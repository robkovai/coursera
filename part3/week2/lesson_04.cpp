#include <iomanip>
#include <iostream>
#include <utility>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "test_runner.h"

using namespace std;

class ReadingManager {
public:
    void Read(int user_id, int page_count) {
        if (userToPage.count(user_id) == 0) {
            userToPage[user_id] = page_count;
            pageToUsers[page_count].insert(user_id);
        } else {
            const int oldPage = userToPage.at(user_id);
            userToPage[user_id] = page_count;

            pageToUsers.at(oldPage).erase(user_id);
            pageToUsers[page_count].insert(user_id);

            if (pageToUsers.at(oldPage).empty())
                pageToUsers.erase(oldPage);
        }
    }

    double Cheer(int user_id) const {
        const int count = static_cast<int>(userToPage.count(user_id));

        if (userToPage.size() == 1 && count == 1)
            return 1;

        if (count == 0)
            return 0;

        const int currentPage = userToPage.at(user_id);
        auto it = pageToUsers.find(currentPage);

        if (it == pageToUsers.begin())
            return 0;

        --it;
        double result = 0;
        for(;; --it) {
            result += it->second.size();
            if (it == pageToUsers.begin())
                break;
        }

        return result / (userToPage.size() - 1);
    }

private:
    std::unordered_map<int, int> userToPage;
    std::map<int, std::unordered_set<int>> pageToUsers;
};

void TestReadingManager1() {
    ReadingManager rm;
    ASSERT_EQUAL(rm.Cheer(5), 0);
    rm.Read(1, 10);
    ASSERT_EQUAL(rm.Cheer(1), 1);
    rm.Read(2, 5);
    rm.Read(3, 7);
    ASSERT_EQUAL(rm.Cheer(2), 0);
    ASSERT_EQUAL(rm.Cheer(3), 0.5);
    rm.Read(3, 10);
    ASSERT_EQUAL(rm.Cheer(3), 0.5);
    rm.Read(3, 11);
    ASSERT_EQUAL(rm.Cheer(3), 1);
    ASSERT_EQUAL(rm.Cheer(1), 0.5);
}

void TestReadingManager2() {
    ReadingManager manager;
    manager.Read(1, 1);
    manager.Read(2, 2);
    manager.Read(3, 3);
    ASSERT_EQUAL(manager.Cheer(2), 0.5);
    manager.Read(4, 4);
    ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
}

void TestReadingManager3() {
    ReadingManager manager;

    ASSERT_EQUAL(0, manager.Cheer(5));
    manager.Read(1, 10);
    ASSERT_EQUAL(1, manager.Cheer(1));
    manager.Read(2, 5);
    manager.Read(3, 7);
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 10);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    manager.Read(3, 11);
    ASSERT_EQUAL(1, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(1));
    manager.Read(2, 11);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(0.5, manager.Cheer(2));
    manager.Read(2, 12);
    ASSERT_EQUAL(0.5, manager.Cheer(3));
    ASSERT_EQUAL(1, manager.Cheer(2));
    manager.Read(1, 13);
    manager.Read(2, 13);
    manager.Read(3, 13);
    ASSERT_EQUAL(0, manager.Cheer(1));
    ASSERT_EQUAL(0, manager.Cheer(2));
    ASSERT_EQUAL(0, manager.Cheer(3));
}

void TestReadingManager4() {
    ReadingManager manager;
    manager.Read(1, 10);
    manager.Read(2, 10);
    manager.Read(3, 9);
    manager.Read(4, 9);
    ASSERT_EQUAL(manager.Cheer(1), 2.0 / 3.0);
    ASSERT_EQUAL(manager.Cheer(2), 2.0 / 3.0);
    ASSERT_EQUAL(manager.Cheer(3), 0);
    ASSERT_EQUAL(manager.Cheer(4), 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TestRunner tr;
    RUN_TEST(tr, TestReadingManager1);
    RUN_TEST(tr, TestReadingManager2);
    RUN_TEST(tr, TestReadingManager3);
    RUN_TEST(tr, TestReadingManager4);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
