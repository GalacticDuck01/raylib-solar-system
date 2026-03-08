#pragma once

#include <vector>

#include "managers/resource_manager.hpp"

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
    ResourceManager* resourceManager = ResourceManager::get();

    Application() = default;
    ~Application() { CloseWindow(); };
    void init(const char* title, int width, int height, unsigned int flags);
    void run();

    void setFPS(unsigned int fps);
private:
    void draw();
};