#include <numeric>
#include <vector>
#include <tuple>

#include "simple_vector.h"
#include "test_runner.h"

using namespace std;

void TestCopyAssignment() {
    SimpleVector<int> numbers(10);
    iota(numbers.begin(), numbers.end(), 1);

    SimpleVector<int> dest;
    ASSERT_EQUAL(dest.Size(), 0u);

    dest = numbers;
    ASSERT_EQUAL(dest.Size(), numbers.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));

    SimpleVector<int> a;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCopyAssignment);
}
