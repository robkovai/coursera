#include <iostream>
#include <map>

using namespace std;

using Countries = map<string, string>;

void commandChangeCapital(Countries &countries) {
    string country, new_capital;
    cin >> country >> new_capital;
    if (!countries.count(country)) {
        countries[country] = new_capital;
        cout << "Introduce new country " << country << " with capital " << new_capital << endl;
    } else {
        if (countries[country] == new_capital) 
            cout << "Country " << country << " hasn't changed its capital" << endl;
        else {
            cout << "Country " << country << " has changed its capital from " << countries[country] << " to " << new_capital << endl;
            countries[country] = new_capital;
        }
    }
}

void commandRename(Countries &countries) {
    string old_country_name, new_country_name;
    cin >> old_country_name >> new_country_name;
    if (old_country_name == new_country_name || !countries.count(old_country_name) || countries.count(new_country_name)) {
        cout << "Incorrect rename, skip" << endl;
        return;
    }
    cout << "Country " << old_country_name << " with capital " << countries[old_country_name] << " has been renamed to " << new_country_name << endl;
    countries[new_country_name] = countries[old_country_name];
    countries.erase(old_country_name);
}

void commandAbout(const Countries &countries) {
    string country;
    cin >> country;
    if (countries.count(country))
        cout << "Country " << country << " has capital " << countries.at(country) << endl;
    else
        cout << "Country " << country << " doesn't exist" << endl;
}

void commandDump(const Countries &countries) {
    if (!countries.size())
        cout << "There are no countries in the world";
    for (const auto &item : countries)
        cout << item.first << "/" << item.second << " ";
    cout << endl;
}

int main() {
    Countries countries;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "CHANGE_CAPITAL") 
            commandChangeCapital(countries);
        else if (command == "RENAME")
            commandRename(countries);
        else if (command == "ABOUT")
            commandAbout(countries);
        else if (command == "DUMP")
            commandDump(countries);
    }

    return 0;
}