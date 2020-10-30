#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int> &numbers) {
	vector<int> result;
	for (int i = numbers.size() - 1; i >= 0; --i)
		result.push_back(numbers[i]);
	return result;
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	auto result = Reversed(numbers);
	for (auto value : result)
		cout << value << endl;
	return 0;
}