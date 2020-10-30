#include <iostream>
#include <vector>

using namespace std;

const vector<int> DaysOfMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

using Affairs = vector<vector<string>>;

void commandAdd(Affairs &affairs) {
	int pos;
	string affair;
	cin >> pos >> affair;
	affairs[pos - 1].push_back(affair);
}

void commandDump(const Affairs &affairs) {
	int pos;
	cin >> pos;
	cout << affairs[pos - 1].size();
	for (const auto &affair : affairs[pos - 1])
		cout << ' ' << affair;
	cout << endl;
}

void commandNext(Affairs &affairs, int &currentMonth) {
	currentMonth = currentMonth == DaysOfMonth.size() - 1 ? 0 : ++currentMonth;
	if (affairs.size() > DaysOfMonth[currentMonth]) {
		auto &lastDay = affairs[DaysOfMonth[currentMonth] - 1];
		for (int i = DaysOfMonth[currentMonth]; i < affairs.size(); ++i)
			lastDay.insert(lastDay.end(), affairs[i].begin(), affairs[i].end());
	}
	affairs.resize(DaysOfMonth[currentMonth]);
}

int main() {
	Affairs affairs;
	int currentMonth = 0;
	affairs.resize(DaysOfMonth[currentMonth]);
	
	int n;
	cin >> n;
	
	for (int i = 0; i < n; ++i) {
		string command;
		cin >> command;
		if (command == "ADD") 
			commandAdd(affairs);
		else if (command == "DUMP") 
			commandDump(affairs);
		else if (command == "NEXT")
			commandNext(affairs, currentMonth);
	}
	
	return 0;
}