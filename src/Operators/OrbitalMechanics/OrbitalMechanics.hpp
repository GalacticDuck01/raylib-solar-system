#pragma once

#include "../Operator.hpp"

#include <PhysicsBody.hpp>

#include <vector>
#include <iostream>
#include <Math.hpp>

using namespace std;

class OrbitalMechanics : public Operator {
private:
    float G = 10.0f;
    float dt = 0.001f;

public:
    vector<PhysicsBody*> bodies = {};

    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void Update() override;
    void CalcFutureStates(int steps);
};