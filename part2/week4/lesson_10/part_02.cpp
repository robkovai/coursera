#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    auto compare = [](const auto &lhs, const auto &rhs) {
        auto length = min(lhs.size(), rhs.size());
        return lhs.substr(0, length) < rhs.substr(0, length);
    };
    auto it_first = lower_bound(range_begin, range_end, prefix, [&compare](const auto &lhs, const auto &rhs) {
        return rhs.size() > lhs.size() ? lhs < rhs : compare(lhs, rhs);
    });
    auto it_second = upper_bound(range_begin, range_end, prefix, [&compare](const auto &lhs, const auto &rhs) {
        return lhs.size() > rhs.size() ? lhs < rhs : compare(lhs, rhs);
    });
    return {it_first, it_second};
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
    const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) 
        cout << *it << " ";
    cout << endl;
  
    const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;
  
    const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}
