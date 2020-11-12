#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (distance(range_begin, range_end) < 3)
        return;
    
    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto it_middle1 = elements.begin();
    advance(it_middle1, elements.size() / 3);
    auto it_middle2 = it_middle1;
    advance(it_middle2, elements.size() / 3);

    MergeSort(elements.begin(), it_middle1);
    MergeSort(it_middle1, it_middle2);
    MergeSort(it_middle2, elements.end());

    vector<typename RandomIt::value_type> temp;

    merge(elements.begin(), it_middle1, it_middle1, it_middle2, back_inserter(temp));
    merge(temp.begin(), temp.end(), it_middle2, elements.end(), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) 
        cout << x << " ";
    cout << endl;

    return 0;
}
