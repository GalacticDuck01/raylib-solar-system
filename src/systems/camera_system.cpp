#include "camera_system.hpp"

void CameraSystem::initialise() {
    thirdPersonCamera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    thirdPersonCamera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    thirdPersonCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    thirdPersonCamera.fovy = 60.0f;                                // Camera field-of-view Y
    thirdPersonCamera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
}

void CameraSystem::update() {
    UpdateCamera(&thirdPersonCamera, CAMERA_THIRD_PERSON);
}

void CameraSystem::sendToShader(const Shader& shader) const {
    SetShaderValue(shader, GetShaderLocation(shader, "cameraPosition"), &thirdPersonCamera.position, SHADER_UNIFORM_VEC3);
}