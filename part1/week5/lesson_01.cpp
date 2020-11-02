#include <iostream> 
#include <exception> 
#include <sstream> 
#include <map>
#include <set>
#include <iomanip>

using namespace std; 

class Date {
public:
    Date() = default;

    Date(int year, int month, int day) {
        this->SetDate(year, month, day);
    }

    int GetYear() const {
        return this->year;
    }

    void SetYear(int year) {
        this->year = year;
    }

    int GetMonth() const {
        return this->month;
    }

    void SetMonth(int month) {
        if (month > 12 || month < 1)
            throw invalid_argument("Month value is invalid: " + to_string(month));
        this->month = month;
    }

    int GetDay() const {
        return this->day;
    }

    void SetDay(int day) {
        if (day > 31 || day < 1)
            throw invalid_argument("Day value is invalid: " + to_string(day));
        this->day = day;
    }

    void SetDate(int year, int month, int day) {
        this->SetYear(year);
        this->SetMonth(month);
        this->SetDay(day);
    }

    friend bool operator<(const Date& lhs, const Date& rhs) {
        return lhs.year == rhs.year ? (lhs.month == rhs.month ? lhs.day < rhs.day : lhs.month < rhs.month) : lhs.year < rhs.year;
    }

    friend istream& operator>>(istream& stream, Date& date) {
        string date_string;
        stream >> date_string;
        stringstream ss(date_string);
        int year, month, day;
        char delimeter1, delimeter2;
        ss >> year >> delimeter1 >> month >> delimeter2 >> day;
        if (ss.fail() || !ss.eof() || delimeter1 != '-' || delimeter2 != '-')
            throw invalid_argument("Wrong date format: " + date_string);
        date.SetDate(year, month, day);
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const Date& date) {
        stream << setfill('0') << setw(4) << date.year << '-' << setw(2) << date.month << '-' << setw(2) << date.day;
        return stream;
    }

private:
    int year = 0;
    int month = 0;
    int day = 0;
};

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        this->data[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (this->data.count(date)) {
            bool erased = this->data.at(date).erase(event) > 0;
            if (this->data.at(date).empty())
                this->DeleteDate(date);
            return erased;
        }
        return false;
    }

    int DeleteDate(const Date& date) {
        int result = this->data.count(date) ? this->data.at(date).size() : 0;
        this->data.erase(date);
        return result;
    }

    void Find(const Date& date) const {
        if (this->data.count(date))
            for (const auto& event : this->data.at(date))
                cout << event << endl;
    }
  
    void Print() const {
        for (const auto& date : this->data) 
            for (const auto &event : date.second)
                cout << date.first << ' ' << event << endl;
    }

private:
    void PrintEvent(const Date& date, const string& event) const {
        cout << date << ' ' << event <<  endl;
    }
    map<Date, set<string>> data;
};

class Parser {
public:
    Parser(Database& db): db(db) {}

    bool ParseLine(const string& line) {
        if (line.empty())
            return true;

        stringstream ss(line);
        string command;
        ss >> command;

        Date date;
        string event;

        try {
            if (command == "Add") {
                ss >> date >> event;
                db.AddEvent(date, event);
            } else if (command == "Del") {
                ss >> date;
                if (!ss.eof()) {
                    ss >> event;
                    cout << (db.DeleteEvent(date, event) ? "Deleted successfully" : "Event not found") << endl;
                } else 
                    cout << "Deleted " << to_string(db.DeleteDate(date)) << " events" <<  endl;
            } else  if (command == "Find") {
                ss >> date;
                db.Find(date);
            } else if (command == "Print") {
                db.Print();
            } else 
                cout << "Unknown command: " << command << endl;
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            return false;
        }
        return true;
    }

private:
    Database& db;
};

int main() {
    Database db;
    Parser parser(db);
    
    string line;
    while (getline(cin, line)) 
        if (!parser.ParseLine(line))
            return 0;

    return 0;
}