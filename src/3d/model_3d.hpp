#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

#include "raylib.h"
#include "node_3d.hpp"

class Model3D : public Node3D {
public:
    Model3D() = default;

    explicit Model3D(const std::string& modelPath) {
        loadModel(modelPath);
    }

    explicit Model3D(Mesh mesh) {
        setMesh(mesh);
    }

    Model3D(const Model3D&) = delete;
    Model3D& operator=(const Model3D&) = delete;

    ~Model3D() {
        unload();
    }

    void loadModel(const std::string& modelPath) {
        if (!FileExists(modelPath.c_str())) {
            throw std::runtime_error("[Model3D::loadModel] Cannot find model file: '" + modelPath + "'");
        }

        unload();
        model = LoadModel(modelPath.c_str());
        loaded = true;
    }

    void setMesh(Mesh mesh) {
        unload();
        this->mesh = mesh;
        UploadMesh(&this->mesh, false);
        model = LoadModelFromMesh(this->mesh);
        loaded = true;
    }

    void setTint(Color tint) { this->tint = tint; }
    Color getTint() const { return tint; }

    void draw() const {
        if (!loaded) return;
        std::cout << "Drawing model at position (" << position.x << ", " << position.y << ", " << position.z << ") with tint (" << tint.r << ", " << tint.g << ", " << tint.b << ", " << tint.a << ")" << std::endl;
        DrawModel(model, position, 1.0f, tint);
    }
private:
    void unload() {
        if (!loaded) return;
        UnloadModel(model);
        model = { 0 };
        mesh = { 0 };
        loaded = false;
    }

    Mesh mesh = { 0 };
    Model model = { 0 };
    Color tint = YELLOW;
    bool loaded = false;
};
