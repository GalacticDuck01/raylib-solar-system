#pragma once

#include "raylib.h"

class Star {
public:
    Star(Vector3 position, float radius, unsigned int nDivisions);

    void draw();
private:
    float radius;
    Vector3 position;
    Mesh mesh;
    Model model;

    void generateIcosphereMesh(unsigned int nDivisions);
};