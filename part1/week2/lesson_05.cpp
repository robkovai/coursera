#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MoveStrings(vector<string> &source, vector<string> &destination) {
	for (auto value : source)
		destination.push_back(value);
	source.clear();
}

int main() {
	vector<string> source = {"a", "b", "c"};
	vector<string> destination = {"z"};
	MoveStrings(source, destination);
	for (auto value : destination)
		cout << value << endl;
	return 0;
}