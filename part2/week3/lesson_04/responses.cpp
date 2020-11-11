#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty())
        os << "No stop";
    else
        for (const auto& bus : r.buses)
            os << bus << " ";
    return os;
}

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
