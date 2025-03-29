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
    float dt = 0.00001f;
    float timeSinceUpdate = 0.f;
    int stepsPerUpdate = 0;

public:
    vector<PhysicsBody*> bodies = {};

    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void Update(float deltaTime) override;
    void ApplyForces();
    void CalcFutureStates(int steps);

    int GetStepsPerUpdate() { return stepsPerUpdate; };
    float GetTimeSinceUpdate() { return timeSinceUpdate; };

    void DrawTrajectories();
};