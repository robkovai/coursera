#include <iostream>
#include <map>
#include <queue>
#include <stdint.h>

#include "test_runner.h"
#include "profile.h"

using namespace std;

using Time = int64_t;

struct Event {
    string hotel_name;
    Time time;
    int client_id;
    int room_count;
};

class Hotel {
public:
    void book(const Event& event) {
        client_rooms[event.client_id] += event.room_count;
        busy_rooms += event.room_count;
    }

    void clear(const Event& event) {
        auto it = client_rooms.find(event.client_id);
        it->second -= event.room_count;
        if (it->second <= 0)
            client_rooms.erase(it);
        busy_rooms -= event.room_count;
    }

    int clients() const {
        return static_cast<int>(client_rooms.size());
    }

    int rooms() const {
        return busy_rooms;
    }

private:
    map<int, int> client_rooms;
    int busy_rooms = 0;
};

class BookingManager {
public:
    void book(const Event& event) {
        hotels[event.hotel_name].book(event);
        events.push(event);
        const auto lastTime = event.time - SecondsInOneDay;
        while (!events.empty()) {
            if (events.front().time <= lastTime)
                clearFrontEvent();
            else
                return;
        }
    }

    int clients(const string& hotel_name) const {
        const auto it = hotels.find(hotel_name);
        return it == hotels.end() ? 0 : it->second.clients();
    }

    int rooms(const string& hotel_name) const {
        const auto it = hotels.find(hotel_name);
        return it == hotels.end() ? 0 : it->second.rooms();
    }

private:
    void clearFrontEvent() {
        const auto& event = events.front();
        hotels.find(event.hotel_name)->second.clear(event);
        events.pop();
    }

    static const int SecondsInOneDay = 86400;

    queue<Event> events;
    map<string, Hotel> hotels;
};

void TestBookingManager() {
    BookingManager manager;
    ASSERT_EQUAL(manager.clients("Marriott"), 0);
    ASSERT_EQUAL(manager.rooms("Marriott"), 0);

    manager.book({ "FourSeasons", 10, 1, 2 });
    manager.book({ "Marriott", 10, 1, 1 });
    manager.book({ "FourSeasons", 86409, 2, 1 });
    ASSERT_EQUAL(manager.clients("FourSeasons"), 2);
    ASSERT_EQUAL(manager.rooms("FourSeasons"), 3);
    ASSERT_EQUAL(manager.clients("Marriott"), 1);

    manager.book({ "Marriott", 86410, 2, 10 });
    ASSERT_EQUAL(manager.rooms("FourSeasons"), 1);
    ASSERT_EQUAL(manager.rooms("Marriott"), 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef DEBUG
    TestRunner tr;
    RUN_TEST(tr, TestBookingManager);
    {
        LOG_DURATION("duration");
        BookingManager manager;
        for (int i = 0; i < 50000; ++i) {
            string hotel = "hotel_" + to_string(i % 10000);
            manager.book({ hotel, i * 1000, i % 1000, 1 });
            manager.clients(hotel);
            manager.rooms(hotel);
        }
    }
#endif

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type, hotel_name;
        cin >> query_type;

        if (query_type == "BOOK") {
            Time time;
            int client_id, room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            manager.book({ hotel_name, time, client_id, room_count });
        } else if (query_type == "CLIENTS") {
            cin >> hotel_name;
            cout << manager.clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            cin >> hotel_name;
            cout << manager.rooms(hotel_name) << "\n";
        }
    }

    return 0;
}
