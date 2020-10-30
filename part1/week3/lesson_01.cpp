#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<int> &v) {
    for (const auto &i : v)
        cout << i << " ";
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto &i : v) 
        cin >> i;

    sort(begin(v), end(v), [](int first, int second) {
        return abs(first) < abs(second);
    });
    
    print(v);
}