#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/*void MakeFile(const string& path) {
    ofstream file(path);
    file << "Keep calm" << endl;
    file << "and" << endl;
    file << "learn C++" << endl;
}*/

void ReadFile(const string& path) {
    ifstream file(path);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

int main() {
    const string Path = "input.txt";
    //MakeFile(Path);
    ReadFile(Path);
    return 0;
}