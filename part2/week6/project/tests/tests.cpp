#include "tests.h"

#include "test_runner.h"

#include "date_test.h"
#include "event_parser_test.h"
#include "condition_parser_test.h"
#include "database_test.h"

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestDate, "TestDate");
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDatabase, "TestDatabase");
}
