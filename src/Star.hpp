#pragma once

#include <raylib.h>

#include "PhysicsBody.hpp"
#include "Icosphere/Icosphere.hpp"

class Star : public PhysicsBody, public Icosphere {
private:
    float radius;
public:
    Star(Color colour, int resolution);

    Color colour;
};