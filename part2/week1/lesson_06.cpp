#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <class T> T Sqr(const T& t);
template <class T> vector<T> Sqr(const vector<T>& v);
template <class First, class Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <class Key, class Value> map<Key, Value> Sqr(const map<Key, Value>& m);

template <class T>
T Sqr(const T& t) {
    return t * t;
}

template <class T>
vector<T> Sqr(const vector<T>& v) {
    vector<T> result;
    for (const auto& i : v)
        result.push_back(Sqr(i));
    return result;
}

template <class First, class Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template <class Key, class Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
    map<Key, Value> result;
    for (const auto& [key, value] : m)
        result[key] = Sqr(value);
    return result;
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) 
        cout << ' ' << x;
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = { {4, {2, 2}}, {7, {4, 3}} };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) 
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;

    return 0;
}