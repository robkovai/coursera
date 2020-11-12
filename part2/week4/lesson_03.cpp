#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto begin_it = s.begin();
    for (auto it = s.begin(); it != s.end();) {
        auto end_it = find(it, s.end(), ' ');
        result.emplace_back(it, end_it);
        if (end_it == s.end()) 
            break;
        it = ++end_it;
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) 
            cout << "/";
        cout << *it;
    }
    cout << endl;
  
  return 0;
}