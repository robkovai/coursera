#include <iostream>
#include <string>

using namespace std;

int main() {
	string text;
	cin >> text;
	int index = -2;
	for (int i = 0; i < text.size(); ++i) {
		if (text[i] == 'f') {
			if (index == -1) {
				index = i;
				break;
			} else
				index = -1;
		}
	}
	cout << index;
	return 0;
}