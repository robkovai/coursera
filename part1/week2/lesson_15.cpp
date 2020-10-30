#include <iostream>
#include <set>

using namespace std;

int main() {
    set<string> values;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string value;
        cin >> value;
        values.insert(value);
    }
    cout << values.size() << endl;
}