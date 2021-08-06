#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

#include "test_runner.h"

using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        auto object = TryAllocate();
        if (!object) {
            object = new T;
            objects.insert(object);
        }
        return object;
    }

    T* TryAllocate() {
        if (free_objects.empty())
            return nullptr;
        auto object  = free_objects.front();
        objects.insert(object);
        free_objects.pop();
        return object;
    }

    void Deallocate(T* object) {
        auto it = objects.find(object);
        if (it == objects.end())
            throw invalid_argument("not found");
        free_objects.push(*it);
        objects.erase(it);
    }

    ~ObjectPool() {
        destroyObjects();
        destroyFreeObjects();
    }

private:
    void destroyObjects() {
        for (auto it = objects.begin(); it != objects.end(); ++it)
            delete *it;
        objects.clear();
    }

    void destroyFreeObjects() {
        while (!free_objects.empty()) {
            delete free_objects.front();
            free_objects.pop();
        }
    }

    set<T*> objects;
    queue<T*> free_objects;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
