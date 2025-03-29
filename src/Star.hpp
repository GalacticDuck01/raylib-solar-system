#pragma once

#include <raylib.h>

#include "PhysicsBody.hpp"
#include "Icosphere/Icosphere.hpp"

class Star : public PhysicsBody, public Icosphere {
private:
    float radius;
public:
    Star(float mass, float radius, vec3 position, vec3 velocity, Color colour, int resolution);

    Color colour;
};