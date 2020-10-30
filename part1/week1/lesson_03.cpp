#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float a, b, c;
    cin >> a >> b >> c;
    if (a == 0 && b == 0)
        return 0;
    if (a == 0) {
        float x = c / -b;
        cout << x;
        return 0;
    }
    float d = pow(b, 2) - 4.0 * a * c;
    if (d > 0) {
        float x1 = (-b + sqrt(d)) / (2.0 * a);
        float x2 = (-b - sqrt(d)) / (2.0 * a);
        cout << x1 << " " << x2;
    } else if (d == 0) {
        float x = -b / (2.0 * a);
        cout << x;
    }
    return 0;
}
