#include <string>
#include <vector>

using namespace std;

#define GET_VARIABLE(line) variable_##line
#define GET_NAME(line) GET_VARIABLE(line)
#define UNIQ_ID GET_NAME(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
