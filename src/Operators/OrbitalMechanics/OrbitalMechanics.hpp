#pragma once

#include "../Operator.hpp"

#include <PhysicsBody.hpp>

#include <vector>
#include <iostream>
#include <Math.hpp>

using namespace std;

class OrbitalMechanics : public Operator {
private:
    vector<PhysicsBody*> bodies;
    float G = 10.0f;

public:
    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void Update() override;
};