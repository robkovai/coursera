#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Man {
public:
    Man(const string& name, const string& type): name(name), type(type) {}

    virtual void Walk(const string& destination) const {
        cout << Log() << " walks to: " << destination << endl;
    }

    string Log() const {
        return type + ": " + name;
    }

    string Name() const {
        return name;
    }

    string Type() const {
        return type;
    }

protected:
    const string name; 
    const string type;  
};

class Student : public Man {
public:
    Student(const string& name, const string& favouriteSong): Man(name, "Student"), favouriteSong(favouriteSong) {}

    void Learn() const {
        cout << Log() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Man::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Log() << " sings a song: " << favouriteSong << endl;
    }

private:
    const string favouriteSong;
};

class Teacher : public Man {
public:
    Teacher(const string& name, const string& subject): Man(name, "Teacher"), subject(subject) {}

    void Teach() const {
        cout << Log() << " teaches: " << subject << endl;
    }

private:
    const string subject;
};

class Policeman : public Man {
public:
    Policeman(const string& name): Man(name, "Policeman") {}

    void Check(const Man& man) const {
        cout << Log() << " checks " << man.Type() << ". " << man.Type() << "'s name is: " << man.Name() << endl;
    }
};

void VisitPlaces(const Man& man, const vector<string> &places) {
    for (const auto& place : places) 
        man.Walk(place);
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
