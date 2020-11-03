#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t count;
    int64_t avg = 0;
    cin >> count;
    if (count <= 0)
        return 0;

    vector<int32_t> values(count);
    for (uint32_t i = 0; i < count; ++i) {
        cin >> values[i];
        avg += values[i];
    }
    avg /= count;
    
    vector<uint32_t> indexes;
    for (uint32_t i = 0; i < count; ++i)
        if (values[i] > avg)
            indexes.push_back(i);

    cout << indexes.size() << endl;            
    for (const auto &value : indexes)
        cout << value << ' ';

    return 0;
}