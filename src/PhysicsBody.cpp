#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody() {}

PhysicsBody::PhysicsBody(vec3 position, vec3 velocity, vec3 acceleration, float mass) {
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->mass = mass;

    futurePositions.push_back({0.f, position});
}

void PhysicsBody::Update(float dt) {

    position += RungeKutta4(velocity, dt);
    velocity += RungeKutta4(acceleration, dt);

    futurePositions.push_back({dt, position});

    if (futurePositions.size() > 8000) futurePositions.pop_front();

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