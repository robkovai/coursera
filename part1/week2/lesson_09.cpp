#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<bool> people;
	for (int i = 0; i < n; ++i) {
		string command;
		cin >> command;
		if (command == "WORRY_COUNT") {
			int count = 0;
			for (const auto &value : people)
				if (value)
					++count;
			cout << count << endl;
		} else {
			int k;
			cin >> k;
			if (command == "COME")
				people.resize(people.size() + k, false);
			else if (command == "WORRY")
				people[k] = true;
			else if (command == "QUIET")
				people[k] = false;
		}
	}
	return 0;
}