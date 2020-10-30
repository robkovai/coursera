#include <iostream>
#include <vector>

using namespace std;

vector<int> inputTemparatures() {
	int n;
	cin >> n;
	vector<int> temperatures(n);
	for (auto &value : temperatures)
		cin >> value;
	return temperatures;
}

int calcAveragedTemparature(const vector<int> &values) {
	int sum = 0;
	for (const auto &value : values)
		sum += value;
	return sum / values.size();
}

vector<int> filterTemperatures(const vector<int> &temparatures, int averaged) {
	vector<int> result;
	for (int i = 0; i < temparatures.size(); ++i)
		if (temparatures[i] > averaged)
			result.push_back(i);
	return result;
}

template<class T>
void printVector(const vector<T> &values) {
	for (const auto &value : values)
		cout << value << ' ';
}

int main() {
	auto temperatures = inputTemparatures();
	auto result = filterTemperatures(temperatures, calcAveragedTemparature(temperatures));
	cout << result.size() << endl;
	printVector(result);
	return 0;
}