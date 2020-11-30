#ifdef DEBUG
#include "test_runner.h"
#endif

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
    Deque() = default;

    bool Empty() const {
        return !Size();
    }

    size_t Size() const {
        return dataBack.size() + dataFront.size();
    }

    T& operator[](size_t pos) {
        return dataFront.size() > pos ? dataFront[dataFront.size() - ++pos] : dataBack[pos - dataFront.size()];
    }

    const T& operator[](size_t pos) const {
        return dataFront.size() > pos ? dataFront[dataFront.size() - ++pos] : dataBack[pos - dataFront.size()];
    }

    T& At(size_t pos) {
        if (pos >= Size())
            throw out_of_range("out of range");
        return operator[](pos);
    }

    const T& At(size_t pos) const {
        if (pos >= Size())
            throw out_of_range("out of range");
        return operator[](pos);
    }

    T& Front() {
        return operator[](0);
    }

    const T& Front() const {
        return operator[](0);
    }

    T& Back() {
        return operator[](Size() - 1);
    }

    const T& Back() const {
        return operator[](Size() - 1);
    }

    void PushFront(const T& value) {
        dataFront.push_back(value);
    }

    void PushBack(const T& value) {
        dataBack.push_back(value);
    }

private:
    vector<T> dataFront, dataBack;
};

#ifdef DEBUG
void TestDequeEmpty() {
    {
        Deque<int> deque;
        ASSERT(deque.Empty());
        deque.PushBack(1);
        ASSERT(!deque.Empty());
        deque.PushFront(2);
        ASSERT(!deque.Empty());
    }
    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT(!deque.Empty());
        deque.PushBack(2);
        ASSERT(!deque.Empty());
    }
}

void TestDequeSize() {
    {
        Deque<int> deque;
        ASSERT_EQUAL(deque.Size(), 0);
        deque.PushBack(1);
        ASSERT_EQUAL(deque.Size(), 1);
        deque.PushFront(2);
        ASSERT_EQUAL(deque.Size(), 2);
    }
    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT_EQUAL(deque.Size(), 1);
        deque.PushBack(2);
        ASSERT_EQUAL(deque.Size(), 2);
    }
}

void TestDequeFront() {
    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT_EQUAL(deque.Front(), 1);
        deque.PushBack(2);
        ASSERT_EQUAL(deque.Front(), 1);
    }
    {
        Deque<int> deque;
        deque.PushBack(2);
        ASSERT_EQUAL(deque.Front(), 2);
        deque.PushFront(1);
        ASSERT_EQUAL(deque.Front(), 1);
    }
}

void TestDequeBack() {
    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT_EQUAL(deque.Back(), 1);
        deque.PushBack(2);
        ASSERT_EQUAL(deque.Back(), 2);
    }
    {
        Deque<int> deque;
        deque.PushBack(2);
        ASSERT_EQUAL(deque.Back(), 2);
        deque.PushFront(1);
        ASSERT_EQUAL(deque.Back(), 2);
    }
}

void TestDequeOperator() {
    {
        Deque<int> deque;
        deque.PushFront(1);
        ASSERT_EQUAL(deque[0], 1);
        deque[0] = 5;
        ASSERT_EQUAL(deque[0], 5);

        deque.PushBack(2);
        ASSERT_EQUAL(deque[0], 5);
        ASSERT_EQUAL(deque[1], 2);
        deque[1] = 6;
        ASSERT_EQUAL(deque[1], 6);
    }
}

void TestDequeAt() {
    {
        Deque<int> deque;
        try {
            deque.At(0);
            ASSERT(false);
        } catch (out_of_range&) {
            ASSERT(true);
        }
        deque.PushBack(1);
        try {
            deque.At(0) = 2;
            ASSERT(true);
        } catch (out_of_range&) {
            ASSERT(false);
        }
        try {
            ASSERT_EQUAL(deque.At(0), 2);
            ASSERT(true);
        } catch (out_of_range&) {
            ASSERT(false);
        }
    }
}
#endif

int main() {
#ifdef DEBUG
    TestRunner tr;
    RUN_TEST(tr, TestDequeEmpty);
    RUN_TEST(tr, TestDequeSize);
    RUN_TEST(tr, TestDequeOperator);
    RUN_TEST(tr, TestDequeAt);
    RUN_TEST(tr, TestDequeFront);
    RUN_TEST(tr, TestDequeBack);
#endif
    return 0;
}
