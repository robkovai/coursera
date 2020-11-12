#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Operation {
    char symbol;
    int number;
};

istream& operator>>(istream& stream, Operation &operation) {
    stream >> operation.symbol >> operation.number;
    return stream;
}

int main() {
    int x, n;
    cin >> x >> n;

    vector<Operation> v(n);

    for (auto &i : v)
        cin >> i;

    for (const auto &i : v)
        cout << '(';

    cout << x;
    for (const auto &i : v)
        cout << ") " << i.symbol << ' ' << i.number;

    return 0;
}
