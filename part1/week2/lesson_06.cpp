#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int> &numbers) {
	vector<int> buffer = numbers;
	numbers.clear();
	for (int i = buffer.size() - 1; i >= 0; --i)
		numbers.push_back(buffer[i]);
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
	for (auto value : numbers)
		cout << value << endl;
	return 0;
}