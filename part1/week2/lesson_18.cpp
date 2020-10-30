#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    map<set<string>, int> buses;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int count;
        cin >> count;
        set<string> stops;
        for (int j = 0; j < count; ++j) {
            string stop;
            cin >> stop;
            stops.insert(stop);
        }
        if (buses.count(stops)) 
            cout << "Already exists for " << buses.at(stops) << endl;
        else {
            int number = buses.size();
            buses[stops] = ++number;
            cout << "New bus " << number << endl;
        }
    }

}