#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        int stop_count;
        is >> q.bus >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops)
            is >> stop;
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES")
        q.type = QueryType::AllBuses;
    return is;
}

struct BusesForStopResponse {
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty())
        os << "No stop";
    else
        for (const auto& bus : r.buses) 
            os << bus << " ";
    return os;
}

struct StopsForBusResponse {
    struct Stop {
        string stop;
        vector<string> buses;
    };
    vector<Stop> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty())
        os << "No bus";
    else
        for (const auto& stop : r.stops) {
            os << "Stop " << stop.stop << ": ";
            if (stop.buses.empty())
                os << "no interchange";
            else
                for (const auto& bus : stop.buses)
                    os << bus << " ";
            os << endl;
        }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses.empty())
        os << "No buses";
    else
        for (const auto& bus : r.buses) {
            os << "Bus " << bus.first << ": ";
            for (const auto& stop : bus.second) 
                os << stop << " ";
            os << endl;
        }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const auto& stop : stops) 
            stops_to_buses[stop].push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (!stops_to_buses.count(stop))
            return {};
        return { stops_to_buses.at(stop) };
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (!buses_to_stops.count(bus))
            return {};

        StopsForBusResponse response;
        for (const auto& stop : buses_to_stops.at(bus)) {
            StopsForBusResponse::Stop value;
            value.stop = stop;
            if (stops_to_buses.at(stop).size() != 1) 
                for (const auto& other_bus : stops_to_buses.at(stop)) 
                    if (bus != other_bus) 
                        value.buses.push_back(other_bus);
            response.stops.push_back(value);
        }
        return response;
    }

    AllBusesResponse GetAllBuses() const {
        return { buses_to_stops };
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}
