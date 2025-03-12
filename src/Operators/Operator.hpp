#pragma once

#include <stdexcept>

using namespace std;

class Operator {
public:
    Operator() {};
    virtual void Update() {throw logic_error("Operator not implemented");};
};