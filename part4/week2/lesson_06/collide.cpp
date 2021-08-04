#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от
// GameObject и реализовывали его интерфейс.

template<typename T>
class Collider : public GameObject {
public:
    bool Collide(const GameObject& that) const override {
        return that.CollideWith(static_cast<const T&>(*this));
    }

    template<typename Other>
    bool Collide(const Other& that) const {
        return geo2d::Collide(static_cast<const T&>(*this).getGeometry(), that.getGeometry());
    }

    bool CollideWith(const Unit& that) const override {
        return this->Collide<Unit>(that);
    }

    bool CollideWith(const Building& that) const override {
        return this->Collide<Building>(that);
    }

    bool CollideWith(const Tower& that) const override {
        return this->Collide<Tower>(that);
    }

    bool CollideWith(const Fence& that) const override {
        return this->Collide<Fence>(that);
    }
};

class Unit : public Collider<Unit> {
public:
    explicit Unit(geo2d::Point position): position(position) {}
    const geo2d::Point& getGeometry() const { return this->position; }

private:
    const geo2d::Point position;
};

class Building : public Collider<Building> {
public:
    explicit Building(geo2d::Rectangle geometry): geometry(geometry) {}
    const geo2d::Rectangle& getGeometry() const { return this->geometry; }

private:
    const geo2d::Rectangle geometry;
};

class Tower : public Collider<Tower> {
public:
    explicit Tower(geo2d::Circle geometry): geometry(geometry) {}
    const geo2d::Circle& getGeometry() const { return this->geometry; }

private:
    const geo2d::Circle geometry;
};

class Fence : public Collider<Fence> {
public:
    explicit Fence(geo2d::Segment geometry): geometry(geometry) {}
    const geo2d::Segment& getGeometry() const { return this->geometry; }

private:
    const geo2d::Segment geometry;
};

// Реализуйте функцию Collide из файла GameObject.h

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}

void TestAddingNewObjectOnMap() {
    // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
    // и мы хотим добавить на неё новый, например, построить новое здание или башню.
    // Мы можем его добавить, только если он не пересекается ни с одним из существующих.
    using namespace geo2d;

    const vector<shared_ptr<GameObject>> game_map = {
        make_shared<Unit>(Point{3, 3}),
        make_shared<Unit>(Point{5, 5}),
        make_shared<Unit>(Point{3, 7}),
        make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
        make_shared<Tower>(Circle{Point{9, 4}, 1}),
        make_shared<Tower>(Circle{Point{10, 7}, 1}),
        make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
    };

    for (size_t i = 0; i < game_map.size(); ++i) {
        Assert(Collide(*game_map[i], *game_map[i]), "An object doesn't collide with itself: " + to_string(i));

        for (size_t j = 0; j < i; ++j) {
            Assert(!Collide(*game_map[i], *game_map[j]), "Unexpected collision found " + to_string(i) + ' ' + to_string(j));
        }
    }

    auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
    ASSERT(!Collide(*new_warehouse, *game_map[0]));
    ASSERT( Collide(*new_warehouse, *game_map[1]));
    ASSERT(!Collide(*new_warehouse, *game_map[2]));
    ASSERT( Collide(*new_warehouse, *game_map[3]));
    ASSERT( Collide(*new_warehouse, *game_map[4]));
    ASSERT(!Collide(*new_warehouse, *game_map[5]));
    ASSERT(!Collide(*new_warehouse, *game_map[6]));

    auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
    ASSERT(!Collide(*new_defense_tower, *game_map[0]));
    ASSERT(!Collide(*new_defense_tower, *game_map[1]));
    ASSERT(!Collide(*new_defense_tower, *game_map[2]));
    ASSERT( Collide(*new_defense_tower, *game_map[3]));
    ASSERT( Collide(*new_defense_tower, *game_map[4]));
    ASSERT(!Collide(*new_defense_tower, *game_map[5]));
    ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestAddingNewObjectOnMap);
    return 0;
}

