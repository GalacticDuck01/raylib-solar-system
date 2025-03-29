#pragma once

#include <raylib.h>
#include <Math.hpp>
#include <iostream>

class PhysicsBody {
public:
    vec3 position = {0.f, 0.f, 0.f};
    vec3 velocity = {0.f, 0.f, 0.f};
    vec3 acceleration = {0.f, 0.f, 0.f};
    float mass = 1.f;

    PhysicsBody();
    PhysicsBody(vec3 position, vec3 velocity, vec3 acceleration, float mass);
    void Update(float dt);

    void ApplyInstantaneousForce(vec3 f) {
        acceleration.x = f.x/mass;
        acceleration.y = f.y/mass;
        acceleration.z = f.z/mass;
    }
    vec3 RungeKutta4(vec3 state, float h);
};