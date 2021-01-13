#include <cstdint>
#include <iterator>

using namespace std;

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

    void PushBack(T&& value) {
        if (size >= capacity) {
            capacity = capacity == 0 ? 1 : 2 * capacity;
            auto new_data = new T[capacity];
            copy(make_move_iterator(begin()), make_move_iterator(end()), new_data);
            delete[] data;
            data = new_data;
        }
        data[size++] = move(value);
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
