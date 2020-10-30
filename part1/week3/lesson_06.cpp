#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class ReversibleString {
public:
    ReversibleString() = default;
    ReversibleString(const string& value): value(value) {}

    void Reverse() {
        reverse(value.begin(), value.end());
    }

    string ToString() const {
        return value;
    }

private:    
    string value;
};

int main() {
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;
  
    s.Reverse();
    const ReversibleString& s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;
  
    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;
  
    return 0;
}
