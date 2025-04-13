#include "Star.hpp"

Star::Star(
    double mass,
    double radius,
    vec3 position,
    vec3 velocity,
    Color colour,
    int resolution)
    : PhysicsBody(position, velocity, {0., 0., 0.}, mass) {

    this->colour = colour;
    this->radius = radius;

    SetResolution(resolution);
}