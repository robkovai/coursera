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

void ReadFile(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile);
    ofstream output(outputFile);
    string line;
    while (getline(input, line)) 
        output << line << endl;
}

int main() {
    const string InputFile = "input.txt";
    const string OutputFile = "output.txt";
    //MakeFile(InputFile);
    ReadFile(InputFile, OutputFile);
    return 0;
}