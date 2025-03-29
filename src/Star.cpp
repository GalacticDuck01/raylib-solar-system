#include "Star.hpp"

Star::Star(
    float mass,
    float radius,
    vec3 position,
    vec3 velocity,
    Color colour,
    int resolution)
    : PhysicsBody(position, velocity, {0.f, 0.f, 0.f}, mass) {

    this->colour = colour;
    this->radius = radius;

    SetResolution(resolution);
}