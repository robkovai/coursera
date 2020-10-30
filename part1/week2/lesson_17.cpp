#include <iostream>
#include <set>
#include <map>

using namespace std;

using Data = map<string, set<string>>;

void commandAdd(Data &data) {
    string word1, word2;
    cin >> word1 >> word2;
    data[word1].insert(word2);
    data[word2].insert(word1);
}

void commandCount(const Data &data) {
    string word;
    cin >> word;
    cout << (data.count(word) ? data.at(word).size() : 0) << endl;
}

void commandCheck(const Data &data) {
    string word1, word2;
    cin >> word1 >> word2;
    cout << (data.count(word1) ? (data.at(word1).count(word2) ? "YES" : "NO") : "NO") << endl;
}

int main() {
    Data data;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "ADD")
            commandAdd(data);
        else if (command == "COUNT")
            commandCount(data);
        else if (command == "CHECK")
            commandCheck(data);
    }
    
    return 0;
}