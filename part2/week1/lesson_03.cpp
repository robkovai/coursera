#include <iostream>
#include <vector>

using namespace std;

int main() {
    int count, density;
    cin >> count >> density;
    if (count <= 0)
        return 0;

    uint64_t sum = 0;
    for (int i = 0; i < count; ++i) {
        uint64_t width, height, length;
        cin >> width >> height >> length;
        sum += width * height * length * density;
    }
    cout << sum;

    return 0;
}