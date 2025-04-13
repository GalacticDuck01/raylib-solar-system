#pragma once

#include "../Operator.hpp"

#include <PhysicsBody.hpp>

#include <vector>
#include <iostream>
#include <Math.hpp>

using namespace std;

class OrbitalMechanics : public Operator {
private:
    double G = 1.0;
    double dt = 0.0001;
    double accumulatedTime = 0.;
    int stepsThisRenderCall = 0;

public:
    vector<PhysicsBody*> bodies = {};

    OrbitalMechanics() : Operator() {};
    void AddBody(PhysicsBody& body);
    void RenderUpdate(double deltaTime) override;
    void ApplyForces();
    void CalcFutureStates(int steps);

    int GetStepsPerUpdate() { return stepsThisRenderCall; };
    double GetAccumulatedTime() { return accumulatedTime; };

    void DrawTrajectories(int nLines = 1000);
};