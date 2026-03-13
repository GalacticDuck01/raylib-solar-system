#pragma once

#include "raylib.h"

class Entity3D {
public:
    Entity3D() = default;
    ~Entity3D() = default;

    virtual void update() {};

    virtual void render(const Shader& shader) const {};

    void setPosition(Vector3 position) { this->position = position; };
    Vector3 getPosition() const { return this->position; };
protected:
    Vector3 position;
};