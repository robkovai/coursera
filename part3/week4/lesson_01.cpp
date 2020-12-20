#include <iostream>
#include <list>
#include <map>

using namespace std;

class Stadium {
public:
    using Sportsmans = list<int>;
    using SportsmansIterator = typename Sportsmans::iterator;
    using SportsmansDictionary = map<int, SportsmansIterator>;

    SportsmansIterator begin() {
        return sportsmans.begin();
    }

    SportsmansIterator end() {
        return sportsmans.end();
    }

    void append(int sportsman, int before) {
        auto it = sportsmansDictionary.find(before);
        sportsmansDictionary[sportsman] = sportsmans.insert(it == sportsmansDictionary.end() ? sportsmans.end() : it->second, sportsman);
    }

private:
    Sportsmans sportsmans;
    SportsmansDictionary sportsmansDictionary;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s1, s2;
    cin >> n;

    Stadium stadium;

    for (int i = 0; i < n; ++i) {
        cin >> s1 >> s2;
        stadium.append(s1, s2);
    }

    for (const auto& value : stadium)
        cout << value << "\n";
}