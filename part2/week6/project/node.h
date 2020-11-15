#pragma once

#include <memory>

#include "date.h"

enum class Comparison { Less, LessOrEqual, Greater, GreaterOrEqual, Equal, NotEqual };

enum class LogicalOperation { Or, And };

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison comp, const Date& date): comp(comp), date(date) {}

    bool Evaluate(const Date& date, const std::string&) const override;

private:
    const Comparison comp;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison comp, const std::string& event): comp(comp), event(event) {}

    bool Evaluate(const Date&, const std::string& event) const override;

private:
    const Comparison comp;
    const std::string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation operation, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs): operation(operation), lhs(lhs), rhs(rhs) {}

    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    const LogicalOperation operation;
    const std::shared_ptr<Node> lhs;
    const std::shared_ptr<Node> rhs;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date&, const std::string&) const override { return true; }
};
