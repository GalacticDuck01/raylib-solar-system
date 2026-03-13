#pragma once

#include <vector>

#include "managers/resource_manager.hpp"
#include "managers/entity_manager.hpp"
#include "systems/camera_system.hpp"

using namespace std;

enum class AppState {
    STARTUP,
    LOADING,
    MENU,
    PAUSED,
    RUNNING,
    GAME_OVER,
    QUITTING
};

class Application {
public:
    AppState state = AppState::STARTUP;
    Camera3D camera = { 0 };
    Shader shader = { 0 };
    EntityManager* entityManager = EntityManager::get();
    ResourceManager* resourceManager = ResourceManager::get();
    CameraSystem* cameraSystem = CameraSystem::get();

    Application() = default;
    ~Application() { CloseWindow(); };
    void init(const char* title, int width, int height, unsigned int flags);
    void run();

    void menuUpdate();
    void runUpdate();

    void setFPS(unsigned int fps);
private:
    void render();
};