#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string text) {
	for (int i = 0; i < text.size() / 2; i++)
		if (text[i] != text[text.size() - i - 1])
			return false;
	return true;
}

vector<string> PalindromFilter(vector<string> values, int minLength) {
	vector<string> result;
	for (auto value : values)
		if (IsPalindrom(value) && value.size() >= minLength)
			result.push_back(value);
	return result;
}

int main() {
	vector<string> values = {"weew", "bro", "code", "aba"};
	auto result = PalindromFilter(values, 3);
	for (auto value : result)
		cout << value << endl;
	return 0;
}