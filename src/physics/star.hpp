#pragma once

#include "raylib.h"
#include "3d/model_3d.hpp"

class Star  : public Model3D {
public:
    Star(Vector3 position, float radius, unsigned int nDivisions);
private:
    float radius;

    void generateIcosphereMesh(unsigned int nDivisions);
};
