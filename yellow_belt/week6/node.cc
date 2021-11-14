#include "node.h"

template<typename T>
bool compare(Comparison cmp, const T &lhs, const T &rhs) {
    switch (cmp) {
        case Comparison::Greater:
            return rhs < lhs;
        case Comparison::GreaterOrEqual:
            return rhs <= lhs;
        case Comparison::Less:
            return lhs < rhs;
        case Comparison::LessOrEqual:
            return lhs <= rhs;
        case Comparison::Equal:
            return lhs == rhs;
        case Comparison::NotEqual:
            return !(lhs == rhs);
        default:
            throw invalid_argument("compare function");
    }
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date_to_compare, const string &event) const {
    return compare(cmp, date_to_compare, date);
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event_to_compare) const {
    return compare(cmp, event_to_compare, event);
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if (logical_operation == LogicalOperation::And) {
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    } else {
        return left->Evaluate(date, event) || right->Evaluate(date, event);
    }
}

DateComparisonNode::DateComparisonNode(Comparison cmp_, const Date &date_)
        : cmp(cmp_), date(date_) {}


EventComparisonNode::EventComparisonNode(Comparison cmp_, const string &event_)
        : cmp(cmp_), event(event_) {}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_operation_,
                                           shared_ptr<Node> left_, shared_ptr<Node> right_)
        : logical_operation(logical_operation_), left(left_), right(right_) {}