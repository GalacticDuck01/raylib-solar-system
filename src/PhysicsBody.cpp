#include "PhysicsBody.hpp"

void PhysicsBody::Update(float dt) {

    position += RungeKutta4(velocity, dt);
    velocity += RungeKutta4(acceleration, dt);

    acceleration = {0.f, 0.f, 0.f};
}

vec3 PhysicsBody::RungeKutta4(vec3 dydt, float h) {
    vec3 k1, k2, k3, k4;

    k1 = dydt;
    k2 = (dydt + k1/2.f);
    k3 = (dydt + k2/2.f);
    k4 = (dydt + k3);

    return (k1 + k2*2 + k3*2 + k4)*h/6.f;
}