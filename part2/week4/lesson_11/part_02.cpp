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

bool Priority(const char &lhs, const char &rhs) {
    bool left = (lhs == '+' || lhs == '-');
    bool right = (rhs == '+' || rhs == '-');
    return left > right;
}

int main() {
    int x, n;
    cin >> x >> n;

    vector<Operation> v(n);

    int count = 0;
    char last_symbol = '*';
    for (auto &i : v) {
        cin >> i;
        if (Priority(last_symbol, i.symbol))
            ++count;
        last_symbol = i.symbol;
    }

    for (int i = 0; i < count; ++i)
        cout << '(';

    cout << x;
    last_symbol = '*';
    for (const auto &i : v) {
        if (Priority(last_symbol, i.symbol))
            cout << ')';
        cout << ' ' << i.symbol << ' ' << i.number;
        last_symbol = i.symbol;
    }

    return 0;
}
