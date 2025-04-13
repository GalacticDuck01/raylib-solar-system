#pragma once

#include <raylib.h>
#include <Math.hpp>
#include <iostream>
#include <deque>
#include <functional>

class PhysicsBody {
public:
    vec3 position = {0., 0., 0.};
    vec3 velocity = {0., 0., 0.};
    vec3 acceleration = {0., 0., 0.};
    double mass = 1.;
    deque<pair<double, vec3>> futurePositions = {};

    PhysicsBody();
    PhysicsBody(vec3 position, vec3 velocity, vec3 acceleration, double mass);
    void Update(double dt);

    void ApplyInstantaneousForce(vec3 f) {
        acceleration.x += f.x/mass;
        acceleration.y += f.y/mass;
        acceleration.z += f.z/mass;
    }
    void DetermineStepSize(double& dt);
    vec3 RungeKutta4(function<vec3(vec3, double)> dydt, vec3 y0, double h);
};