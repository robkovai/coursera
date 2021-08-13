#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T *t = nullptr;

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator = (const UniquePtr&) = delete;

public:
    UniquePtr() = default;

    UniquePtr(T* ptr): t(ptr) {}

    UniquePtr(UniquePtr&& other) {
        t = other.t;
        other.t = nullptr;
    }

    UniquePtr& operator = (nullptr_t) {
        delete t;
        t = nullptr;
        return *this;
    }

    UniquePtr& operator = (UniquePtr&& other) {
        if (this != &other) {
            Reset(other.t);
            other.t = nullptr;
        }
        return *this;
    }

    ~UniquePtr() {
        delete t;
    }

    T& operator * () const {
        return *t;
    }

    T * operator -> () const {
        return t;
    }

    T * Release() {
        auto result = t;
        t = nullptr;
        return result;
    }

    void Reset(T * ptr) {
        delete t;
        t = ptr;
    }

    void Swap(UniquePtr& other) {
        swap(t, other.t);
    }

    T * Get() const {
        return t;
    }
};


struct Item {
    static int counter;
    int value;
    Item(int v = 0): value(v) {
        ++counter;
    }
    Item(const Item& other): value(other.value) {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;


void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}
