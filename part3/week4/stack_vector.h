#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    using Data = array<T, N>;
    using Iterator = typename Data::iterator;
    using ConstIterator = typename Data::const_iterator;

    explicit StackVector(size_t size = 0) {
        if (size > N)
            throw invalid_argument("size > capacity");
        this->size = size;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    Iterator begin() {
        return data.begin();
    }

    Iterator end() {
        return next(data.begin(), size);
    }

    ConstIterator begin() const {
        return data.begin();
    }

    ConstIterator end() const {
        return next(data.begin(), size);
    }

    size_t Size() const {
        return size;
    }

    size_t Capacity() const {
        return N;
    }

    void PushBack(const T& value) {
        if (size == N)
            throw overflow_error("vector is full");
        data[size++] = value;
    }

    T PopBack() {
        if (size == 0)
            throw underflow_error("vector is empty");
        return data[--size];
    }

private:
    array<T, N> data;
    size_t size = 0;
};

