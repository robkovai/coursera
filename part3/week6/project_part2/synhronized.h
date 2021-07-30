#pragma once

#include <mutex>

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()): value(std::move(initial)) {}

    struct Access {
        std::lock_guard<std::mutex> guard;
        T& ref_to_value;
    };

    Access GetAccess() {
        return { std::lock_guard(m), value };
    }

private:
    T value;
    std::mutex m;
};
