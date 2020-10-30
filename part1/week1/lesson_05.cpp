#include <iostream>

using namespace std;

int main() {
	float n, a, b, x, y;
	cin >> n >> a >> b >> x >> y;
	float discount = 0;
	if (n > b)
		discount = y;
	else if (n > a)
		discount = x;
	cout << n - discount / 100 * n;
	return 0;
}