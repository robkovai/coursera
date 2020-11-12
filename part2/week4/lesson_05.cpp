#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    generate(v.begin(), v.end(), [&n]() { return n--; });

    do {
        for (const auto& value : v)
            cout << value << ' ';
        cout << endl;
    } while (prev_permutation(v.begin(), v.end()));

    return 0;
}
