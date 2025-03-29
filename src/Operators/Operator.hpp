#pragma once

#include <stdexcept>

using namespace std;

class Operator {
public:
    Operator() {};
    virtual void Update(float deltaTime) {throw logic_error("Operator not implemented");};
};