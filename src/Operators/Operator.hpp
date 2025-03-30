#pragma once

#include <stdexcept>

using namespace std;

class Operator {
public:
    Operator() {};
    virtual void RenderUpdate(float deltaTime) {throw logic_error("Operator not implemented");};
};