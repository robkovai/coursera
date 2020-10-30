#include <iostream>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(const string& value) {
    map<char, int> result;
    for (const auto &item : value) 
        ++result[item];
    return result;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string first, second;
        cin >> first >> second;
        cout << (BuildCharCounters(first) == BuildCharCounters(second) ? "YES" : "NO") << endl;
    }

    return 0;
}