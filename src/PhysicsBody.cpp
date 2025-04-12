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

    auto dvdt = [&](vec3 r, float t) { return acceleration; };
    auto drdt = [&](vec3 r, float t) { return velocity; };

    position += RungeKutta4(drdt, position, dt);
    velocity += RungeKutta4(dvdt, velocity, dt);

    futurePositions.push_back({dt, position});

    acceleration = {0.f, 0.f, 0.f};
}

void PhysicsBody::DetermineStepSize(float& dt) {
    auto dvdt = [&](vec3 r, float t) { return acceleration; };
    auto drdt = [&](vec3 r, float t) { return velocity; };

    auto CalcError = [&]() {
        float dv = velocity.magnitude() + RungeKutta4(dvdt, velocity + RungeKutta4(dvdt, velocity, dt), dt).magnitude();
        float dv2 = velocity.magnitude() + RungeKutta4(dvdt, velocity, 2.0f*dt).magnitude();
        float error = (1.f/30.f)*(dv2 - dv)/dv;
        return error;
    };

    // Note: This could be useful for the timestepping issue https://www.gafferongames.com/post/fix_your_timestep/

    float acceptableError = 1e-7;

    float error = CalcError();
    while (error > acceptableError) {
        dt *= 0.9f*pow(acceptableError/error, 0.25);
        error = CalcError();
    }
}

vec3 PhysicsBody::RungeKutta4(function<vec3(vec3, float)> dydt, vec3 y0, float h) {
    vec3 k1, k2, k3, k4;

    float t0 = 0.f;
    float halfH = h/2.f;

    k1 = dydt(y0, t0);
    k2 = dydt(y0 + k1*halfH, t0 + halfH);
    k3 = dydt(y0 + k2*halfH, t0 + halfH);
    k4 = dydt(y0 + k3*h, t0 + h);

    vec3 y1 = (k1 + k2*2 + k3*2 + k4)*h/6.f;
    return y1;
}