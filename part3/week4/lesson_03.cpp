#include <string>
#include <vector>
#include <set>

#include "test_runner.h"

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        auto itSource = data.insert(string(source)).first;
        auto itTarget = data.insert(string(target)).first;
        sourceToTarget[*itSource] = *itTarget;
        targetToSource[*itTarget] = *itSource;
    }

    string_view TranslateForward(string_view source) const {
        auto it = sourceToTarget.find(source);
        return it == sourceToTarget.end() ? "" : it->second;
    }

    string_view TranslateBackward(string_view target) const {
        auto it = targetToSource.find(target);
        return it == targetToSource.end() ? "" : it->second;
    }

private:
    set<string> data;
    map<string_view, string_view> sourceToTarget, targetToSource;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
