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
    float timeSinceUpdate = 0.f;
    int stepsThisUpdate = 0;

public:
    vector<PhysicsBody*> bodies = {};

    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void RenderUpdate(float deltaTime) override;
    void ApplyForces();
    void CalcFutureStates(int steps);

    int GetStepsPerUpdate() { return stepsThisUpdate; };
    float GetTimeSinceUpdate() { return timeSinceUpdate; };

    void DrawTrajectories(int nLines = 1000);
};