#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

using Bus = string;
using Buses = vector<Bus>;
using Stop = string;
using Stops = vector<Stop>;

struct Data {
    map<Stop, Buses> stop_to_buses;
    map<Bus, Stops> bus_to_stops;
};

void commandNewBus(Data &data) {
    Bus bus;
    int n;
    cin >> bus >> n;
    for (int i = 0; i < n; ++i) {
        Stop stop;
        cin >> stop;
        data.stop_to_buses[stop].push_back(bus);
        data.bus_to_stops[bus].push_back(stop);
    }
}

void commandBusesForStop(const Data &data) {
    Stop stop;
    cin >> stop;
    if (!data.stop_to_buses.count(stop)) {
        cout << "No stop" << endl;
        return;
    }
    for (const auto &bus : data.stop_to_buses.at(stop)) 
        cout << bus << " ";
    cout << endl;
}

void commandStopsForBus(const Data &data) {
    Bus current_bus;
    cin >> current_bus;
    if (!data.bus_to_stops.count(current_bus)) {
        cout << "No bus" << endl;
        return;
    }
    for (const auto &stop : data.bus_to_stops.at(current_bus)) {
        cout << "Stop " << stop << ":";
        Buses buses;
        for (const auto &bus : data.stop_to_buses.at(stop)) 
            if (bus != current_bus)
                buses.push_back(bus);
        if (buses.empty())
            cout << " no interchange";
        else
            for (const auto &bus : buses)
                cout << " " << bus;
        cout << endl;
    }
}

void commandAllBuses(const Data &data) {
    if (data.bus_to_stops.empty()) {
        cout << "No buses" << endl;
        return;
    }
    for (const auto &bus : data.bus_to_stops) {
        cout << "Bus " << bus.first << ":";
        for (const auto &stop : bus.second) 
            cout << " " << stop;
        cout << endl;
    }
}

int main() {
    Data data;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "NEW_BUS")
            commandNewBus(data);
        else if (command == "BUSES_FOR_STOP")
            commandBusesForStop(data);
        else if (command == "STOPS_FOR_BUS")
            commandStopsForBus(data);
        else if (command == "ALL_BUSES")
            commandAllBuses(data);
    }

}