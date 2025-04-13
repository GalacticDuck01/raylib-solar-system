#pragma once

#include <stdexcept>

using namespace std;

class Operator {
public:
    Operator() {};
    virtual void RenderUpdate(double deltaTime) {throw logic_error("Operator not implemented");};
};