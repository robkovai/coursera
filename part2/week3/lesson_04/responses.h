#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

struct BusesForStopResponse {
    std::vector<std::string> buses;
};
std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    struct Stop {
        std::string stop;
        std::vector<std::string> buses;
    };
    std::vector<Stop> stops;
};
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> buses;
};
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
