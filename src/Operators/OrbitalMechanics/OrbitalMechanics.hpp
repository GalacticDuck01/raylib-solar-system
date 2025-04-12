#pragma once

#include "../Operator.hpp"

#include <PhysicsBody.hpp>

#include <vector>
#include <iostream>
#include <Math.hpp>

using namespace std;

class OrbitalMechanics : public Operator {
private:
    float G = 1.0f;
    float dt = 0.0001f;
    float accumulatedTime = 0.f;
    int stepsThisRenderCall = 0;

public:
    vector<PhysicsBody*> bodies = {};

    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void RenderUpdate(float deltaTime) override;
    void ApplyForces();
    void CalcFutureStates(int steps);

    int GetStepsPerUpdate() { return stepsThisRenderCall; };
    float GetAccumulatedTime() { return accumulatedTime; };

    void DrawTrajectories(int nLines = 1000);
};