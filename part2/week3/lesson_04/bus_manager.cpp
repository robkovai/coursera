#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto& stop : stops)
        stops_to_buses[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    if (!stops_to_buses.count(stop))
        return {};
    return { stops_to_buses.at(stop) };
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    return { buses_to_stops };
}
