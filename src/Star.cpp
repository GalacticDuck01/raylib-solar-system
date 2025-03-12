#include "Star.hpp"

Star::Star(Color colour, int resolution) {
    this->colour = colour;
    this->radius = 1.0f;

    SetResolution(resolution);
}