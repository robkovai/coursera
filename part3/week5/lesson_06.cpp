#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (distance(range_begin, range_end) < 2)
        return;

    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

    auto it_middle1 = elements.begin();
    advance(it_middle1, elements.size() / 3);
    auto it_middle2 = it_middle1;
    advance(it_middle2, elements.size() / 3);

    MergeSort(elements.begin(), it_middle1);
    MergeSort(it_middle1, it_middle2);
    MergeSort(it_middle2, elements.end());

    vector<typename RandomIt::value_type> temp;

    merge(make_move_iterator(elements.begin()), make_move_iterator(it_middle1),
          make_move_iterator(it_middle1), make_move_iterator(it_middle2), back_inserter(temp));

    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
          make_move_iterator(it_middle2), make_move_iterator(elements.end()), range_begin);

}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
