#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void MakeFile(const string& path) {
    ofstream file(path);
    file << "2 3" << endl;
    file << "1,2,3" << endl;
    file << "4,5,6" << endl;
}

void ReadFile(const string& inputFile) {
    ifstream input(inputFile);
    int x, y;
    input >> x >> y;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            int value;
            input >> value;
            cout << setw(10) << value;
            if (j != y - 1) {
                input.ignore(1);
                cout << ' ';
            }
        }
        if (i != x - 1)
            cout << endl;
    }
}

int main() {
    const string InputFile = "input.txt";
    //MakeFile(InputFile);
    ReadFile(InputFile);
    return 0;
}