#include <iostream>

using namespace std;

struct Specialization {
    explicit Specialization(string value): value(value) {}
    string value;
};

struct Course {
    explicit Course(string value): value(value) {}
    string value;
};

struct Week {
    explicit Week(string value): value(value) {}
    string value;
};

struct LectureTitle {
    LectureTitle(Specialization specialization, Course course, Week week):
        specialization(specialization.value), course(course.value), week(week.value) {}
    string specialization;
    string course;
    string week;
};

int main() {
    LectureTitle title(Specialization("C++"), Course("White belt"), Week("4th"));
    return 0;
}