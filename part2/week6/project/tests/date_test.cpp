#include "date_test.h"

#include <sstream>

#include "test_runner.h"
#include "date.h"

using namespace std;

void TestDate() {
    {
        istringstream is("2017-11-18");
        AssertEqual(ParseDate(is), Date(2017, 11, 18), "Parse date 2017-11-18");
    }
    {
        istringstream is("0-2-31");
        AssertEqual(ParseDate(is), Date(0, 2, 31), "Parse date 0-2-31");
    }
    Assert(Date(2020, 1, 1) < Date(2020, 1, 2), "Date 2020-01-01 < 2020-01-02");
    Assert(Date(2020, 1, 2) > Date(2020, 1, 1), "Date 2020-01-02 > 2020-01-01");
    Assert(Date(2020, 1, 1) <= Date(2020, 1, 2), "Date 2020-01-01 <= 2020-01-02");
    Assert(Date(2020, 1, 2) <= Date(2020, 1, 2), "Date 2020-01-02 <= 2020-01-02");
    Assert(Date(2020, 1, 2) >= Date(2020, 1, 1), "Date 2020-01-02 >= 2020-01-01");
    Assert(Date(2020, 1, 2) >= Date(2020, 1, 2), "Date 2020-01-02 >= 2020-01-02");
    Assert(Date(2020, 1, 2) == Date(2020, 1, 2), "Date 2020-01-02 == 2020-01-02");
    Assert(Date(2020, 1, 1) != Date(2020, 1, 2), "Date 2020-01-01 != 2020-01-02");
}
