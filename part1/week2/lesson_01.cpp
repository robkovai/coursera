#include <iostream>

using namespace std;

int Factorial(int n) {
	return n <= 0 ? 1 : Factorial(n - 1) * n;
}

int main() {
	int n;
	cin >> n;
	cout << Factorial(n);
	return 0;
}