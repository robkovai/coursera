#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const std::string&) const {
    switch (this->comp) {
        case Comparison::Less:              return date < this->date;
        case Comparison::LessOrEqual:       return date <= this->date;
        case Comparison::Greater:           return date > this->date;
        case Comparison::GreaterOrEqual:    return date >= this->date;
        case Comparison::Equal:             return date == this->date;
        case Comparison::NotEqual:          return date != this->date;
        default: return false;
    }
}

bool EventComparisonNode::Evaluate(const Date&, const std::string& event) const {
    switch (this->comp) {
        case Comparison::Less:              return event < this->event;
        case Comparison::LessOrEqual:       return event <= this->event;
        case Comparison::Greater:           return event > this->event;
        case Comparison::GreaterOrEqual:    return event >= this->event;
        case Comparison::Equal:             return event == this->event;
        case Comparison::NotEqual:          return event != this->event;
        default: return false;
    }
}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    switch (this->operation) {
        case LogicalOperation::And: return this->lhs->Evaluate(date, event) && this->rhs->Evaluate(date, event);
        case LogicalOperation::Or: return this->lhs->Evaluate(date, event) || this->rhs->Evaluate(date, event);
        default: return false;
    }
}
