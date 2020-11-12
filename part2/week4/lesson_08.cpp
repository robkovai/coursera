#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    if (numbers.empty())
        return numbers.end();

    auto it = numbers.equal_range(border);
    if (it.first != it.second)
        return it.first;

    if (it.first == numbers.end())
        return prev(numbers.end());

    if (it.first == numbers.begin())
        return it.first;
    
    int first_diff = border - *prev(it.first);
    int second_diff = *it.first - border;
    if (first_diff <= second_diff)
        return prev(it.first);

    return it.first;
}

int main() {
    set<int> numbers = {1, 4, 6};
    cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << endl;
      
    set<int> empty_set;
  
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}
