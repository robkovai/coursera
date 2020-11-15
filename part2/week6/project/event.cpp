#include "event.h"

using namespace std;

string ParseEvent(istream& is) {
    string line;
    getline(is, line);
    if (!line.empty())
        if (line.front() == ' ') {
            const auto strBegin = line.find_first_not_of(" \t");
            return line.substr(strBegin, line.size() - strBegin);
        }
   return line;
}
