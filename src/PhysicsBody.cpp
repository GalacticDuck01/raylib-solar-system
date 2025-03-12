#include "PhysicsBody.hpp"

void PhysicsBody::Update(float dt) {
    float h = dt;

    vec3 k1, k2, k3, k4;

    k1 = velocity*h;
    k2 = (velocity + k1/2.f)*h;
    k3 = (velocity + k2/2.f)*h;
    k4 = (velocity + k3)*h;
    position += (k1 + k2*2 + k3*2 + k4)/6.f;
    
    k1 = acceleration*h;
    k2 = (acceleration + k1/2.f)*h;
    k3 = (acceleration + k2/2.f)*h;
    k4 = (acceleration + k3)*h;
    velocity += (k1 + k2*2 + k3*2 + k4)/6.f;

    acceleration = {0.f, 0.f, 0.f};
}