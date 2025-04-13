#include "PhysicsBody.hpp"

PhysicsBody::PhysicsBody() {}

PhysicsBody::PhysicsBody(vec3 position, vec3 velocity, vec3 acceleration, double mass) {
    this->position = position;
    this->velocity = velocity;
    this->acceleration = acceleration;
    this->mass = mass;

    futurePositions.push_back({0., position});
}

void PhysicsBody::Update(double dt) {

    auto dvdt = [&](vec3 r, double t) { return acceleration; };
    auto drdt = [&](vec3 r, double t) { return velocity; };

    position += RungeKutta4(drdt, position, dt);
    velocity += RungeKutta4(dvdt, velocity, dt);

    futurePositions.push_back({dt, position});

    acceleration = {0., 0., 0.};
}

void PhysicsBody::DetermineStepSize(double& dt) {
    auto dvdt = [&](vec3 r, double t) { return acceleration; };
    auto drdt = [&](vec3 r, double t) { return velocity; };

    auto CalcError = [&]() {
        double dr = position.magnitude() + RungeKutta4(drdt, position + RungeKutta4(drdt, position, dt), dt).magnitude();
        double dr2 = position.magnitude() + RungeKutta4(drdt, position, 2.0*dt).magnitude();
        double error = (1./30.)*(dr2 - dr)/dr;
        return error;
    };

    // Note: This could be useful for the timestepping issue https://www.gafferongames.com/post/fix_your_timestep/

    double acceptableError = 1e-6;

    double error = CalcError();
    while (error > acceptableError) {
        dt *= 0.9*pow(acceptableError/error, 0.25);
        error = CalcError();
    }
}

vec3 PhysicsBody::RungeKutta4(function<vec3(vec3, double)> dydt, vec3 y0, double h) {
    vec3 k1, k2, k3, k4;

    double t0 = 0.;
    double halfH = h/2.;

    k1 = dydt(y0, t0);
    k2 = dydt(y0 + k1*halfH, t0 + halfH);
    k3 = dydt(y0 + k2*halfH, t0 + halfH);
    k4 = dydt(y0 + k3*h, t0 + h);

    vec3 y1 = (k1 + k2*2 + k3*2 + k4)*h/6.;
    return y1;
}