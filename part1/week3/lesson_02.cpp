#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void print(const vector<string> &v) {
    for (const auto &i : v)
        cout << i << " ";
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<string> v(n);
    for (auto &i : v) 
        cin >> i;

    sort(begin(v), end(v), [](string first, string second) {
        transform(first.begin(), first.end(), first.begin(), [](unsigned char c) { return tolower(c); });
        transform(second.begin(), second.end(), second.begin(), [](unsigned char c) { return tolower(c); });
        return first < second;
    });

    print(v);
}