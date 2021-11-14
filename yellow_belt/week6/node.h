#pragma once

#include "date.h"
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date &date, const string &event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp_, const Date &date_);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    Comparison cmp;
    Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp_, const string &event_);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    Comparison cmp;
    string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation logical_operation_,
                         shared_ptr<Node> left_, shared_ptr<Node> right_);

    bool Evaluate(const Date &date, const string &event) const override;

private:
    LogicalOperation logical_operation;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

void TestDateComparisonNode();

void TestEventComparisonNode();

void TestLogicalOperationNode();