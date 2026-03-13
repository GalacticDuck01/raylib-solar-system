#pragma once

#include "raylib.h"

class CameraSystem {
public:
    static CameraSystem* get() {
        static CameraSystem instance;
        return &instance;
    }

    CameraSystem(const CameraSystem&) = delete;
    CameraSystem& operator=(const CameraSystem&) = delete;

    void initialise();
    void update();

    void beginMode3D() const { BeginMode3D(thirdPersonCamera); }
    void endMode3D() const { EndMode3D(); }

    void sendToShader(const Shader& shader) const;

private:
    Camera thirdPersonCamera = { 0 };

    CameraSystem() = default;
    ~CameraSystem() = default;
};