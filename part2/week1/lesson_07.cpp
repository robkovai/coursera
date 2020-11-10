#include <iostream>
#include <map>

using namespace std;

template <class Key, class Value>
Value& GetRefStrict(map<Key, Value>& m, const Key& k) {
    if (!m.count(k))
        throw runtime_error("not found");
    return m[k];
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;

    return 0;
}