#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void MakeFile(const string& path) {
    ofstream file(path);
    file << 5 << endl;
    file << 0.34567 << endl;
    file << 10.4 << endl;
}

void ReadFile(const string& inputFile) {
    ifstream input(inputFile);
    string line;
    cout << fixed << setprecision(3);
    while (getline(input, line)) 
        cout << atof(line.data()) << endl;
}

int main() {
    const string InputFile = "input.txt";
    //MakeFile(InputFile);
    ReadFile(InputFile);
    return 0;
}