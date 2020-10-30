#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class SortedStrings {
public:
    void AddString(const string& s) {
        values.push_back(s);
    }

    vector<string> GetSortedStrings() {
        vector<string> result = values;
        sort(begin(result), end(result));
        return result;
    }

private:
    vector<string> values;
};

void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) 
        cout << s << " ";
    cout << endl;
}

int main() {
    SortedStrings strings;
  
    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);
  
    strings.AddString("second");
    PrintSortedStrings(strings);
  
  return 0;
}