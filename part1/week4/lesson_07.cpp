#include <iostream>
#include <vector>

using namespace std;

struct Student {
    string name;
    string surname;
    int day;
    int month;
    int year;
};

using Students = vector<Student>;

void ReadStudents(Students &students) {
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        Student student;
        cin >> student.name >> student.surname >> student.day >> student.month >> student.year;
        students.push_back(student);
    }
}

void ReadQueries(const Students &students) {
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        string command;
        int number;
        cin >> command >> number;
        if (number <= 0) {
            cout << "bad request" << endl;
            continue;
        }
        if (number > students.size()) {
            cout << "bad request" << endl;
            continue;
        }
        const Student &student = students.at(--number);
        if (command == "name") 
            cout << student.name << ' ' << student.surname << endl;
        else if (command == "date")
            cout << student.day << '.' << student.month << '.' << student.year << endl;
        else
            cout << "bad request" << endl;
    }
}

int main() {
    Students students;
    ReadStudents(students);
    ReadQueries(students);
    return 0;
}