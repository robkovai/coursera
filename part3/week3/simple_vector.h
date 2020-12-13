#pragma once

#include <cstdlib>
#include <cstring>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size): data(new T[size]), size(size), capacity(size) {}

    ~SimpleVector() {
        delete[] data;
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

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return capacity;
    }

    void PushBack(const T& value) {
        if (size == capacity) {
            capacity = size == 0 ? 1 : capacity * 2;
            T* temp = new T[capacity];
            if (data != nullptr) {
                memcpy(temp, data, size * sizeof(T));
                delete[] data;
            }
            data = temp;
        }
        data[size++] = value;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};
