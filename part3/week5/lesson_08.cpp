#include <vector>
#include <future>
#include <numeric>

#include "test_runner.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end): it_begin(begin), it_end(end), range_size(distance(it_begin, it_end)) {}

    Iterator begin() const {
        return it_begin;
    }

    Iterator end() const {
        return it_end;
    }

    size_t size() const {
        return range_size;
    }

private:
    Iterator it_begin, it_end;
    size_t range_size;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (auto it = begin; distance(it, end) > 0; it = next(it, page_size))
            result.emplace_back(it, next(it, min(page_size, size_t(distance(it, end)))));
    }

    auto begin() const {
        return result.begin();
    }

    auto end() const {
        return result.end();
    }

    size_t size() const {
        return result.size();
    }

private:
    vector<IteratorRange<Iterator>> result;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    vector<future<int64_t>> futures;
    for (const auto& page : Paginate(matrix, max(int(matrix.size() / thread::hardware_concurrency()), 1))) {
        futures.push_back(async([page] {
            int64_t result = 0;
            for (auto it = page.begin(); it != page.end(); ++it)
                result += accumulate(it->begin(), it->end(), 0);
            return result;
        }));
    }
    int64_t result = 0;
    for (auto& future : futures)
        result += future.get();

    return result;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
