#pragma once

namespace RAII {

template<typename Provider>
class Booking {
public:
    Provider *provider;
    int counter;

    Booking(Provider* provider, int counter): provider(provider), counter(counter) {}

    Booking(const Booking&) = delete;

    Booking(Booking &&other): provider(other.provider), counter(other.counter) {
        other.provider = nullptr;
    }

    Booking& operator=(const Booking&) = delete;

    Booking& operator=(Booking &&other) {
        if (this != &other) {
            delete provider;
            provider = other.provider;
            other.provider = nullptr;
        }
        return *this;
    }

    ~Booking() {
        if (provider)
            provider->CancelOrComplete(*this);
    }
};

} // RAII
