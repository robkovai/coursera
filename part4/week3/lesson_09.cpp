#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

namespace Nodes {

class Value : public Expression {
    int value = 0;

public:
    explicit Value(int value): value(value) {}

    int Evaluate() const override {
        return this->value;
    }

    std::string ToString() const override {
        return to_string(this->value);
    }
};

class Sum : public Expression {
    ExpressionPtr left, right;

public:
    explicit Sum(ExpressionPtr left, ExpressionPtr right): left(move(left)), right(move(right)) {}

    int Evaluate() const override {
        return this->left->Evaluate() + this->right->Evaluate();
    }

    std::string ToString() const override {
        return "(" + this->left->ToString() + ")+(" + this->right->ToString() + ")";
    }
};

class Product : public Expression {
    ExpressionPtr left, right;

public:
    explicit Product(ExpressionPtr left, ExpressionPtr right): left(move(left)), right(move(right)) {}

    int Evaluate() const override {
        return this->left->Evaluate() * this->right->Evaluate();
    }

    std::string ToString() const override {
        return "(" + this->left->ToString() + ")*(" + this->right->ToString() + ")";
    }
};

} // Nodes

ExpressionPtr Value(int value) {
    return make_unique<Nodes::Value>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<Nodes::Sum>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<Nodes::Product>(move(left), move(right));
}

string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}
