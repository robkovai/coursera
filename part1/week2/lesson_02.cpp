#include <iostream>
#include <string>

using namespace std;

bool IsPalindrom(string text) {
	for (int i = 0; i < text.size() / 2; i++)
		if (text[i] != text[text.size() - i - 1])
			return false;
	return true;
}

int main() {
	string text;
	cin >> text;
	cout << boolalpha << IsPalindrom(text);
	return 0;
}