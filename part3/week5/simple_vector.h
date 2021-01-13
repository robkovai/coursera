#pragma once

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size): data(new T[size]), size(size), capacity(size) {}

    SimpleVector(const SimpleVector& other): data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        std::copy(other.begin(), other.end(), begin());
    }

    ~SimpleVector() {
        delete[] data;
    }

    void operator=(const SimpleVector& other) {
        if (capacity >= other.size) {
            std::copy(other.begin(), other.end(), begin());
            size = other.size;
        } else {
            SimpleVector<T> temp(other);
            std::swap(temp.data, data);
            std::swap(temp.size, size);
            std::swap(temp.capacity, capacity);
        }
    }

    T& operator[](size_t index) {
        return data[index];
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size;
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    void PushBack(const T& value) {
        if (size >= capacity) {
            capacity = capacity == 0 ? 1 : 2 * capacity;
            auto new_data = new T[capacity];
            copy(begin(), end(), new_data);
            delete[] data;
            data = new_data;
        }
        data[size++] = value;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};
