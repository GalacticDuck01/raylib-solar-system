#pragma once

#include "raylib.h"

class Node3D {
public:
    Node3D() = default;
    ~Node3D() = default;

    virtual void update() {};

    virtual void draw() const {};

    void setPosition(Vector3 position) { this->position = position; };
    Vector3 getPosition() const { return this->position; };
protected:
    Vector3 position;
};