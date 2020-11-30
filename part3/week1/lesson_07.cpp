#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
public:
    Table(size_t rows, size_t columns) {
        Resize(rows, columns);
    }

    void Resize(size_t rows, size_t columns) {
        if (rows == 0 || columns == 0) {
            rows = columns = 0;
            data.clear();
            return;
        }
        data.resize(rows);
        for (auto& row : data)
            row.resize(columns);
    }

    pair<size_t, size_t> Size() const {
        return make_pair(data.size(), data.empty() ? 0 : data.at(0).size());
    }

    vector<T>& operator[](size_t pos) {
        return data[pos];
    }

    const vector<T>& operator[](size_t pos) const {
        return data[pos];
    }

private:
    vector<vector<T>> data;
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
