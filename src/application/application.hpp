#pragma once

#include <vector>

#include "managers/resource_manager.hpp"
#include "physics/star.hpp"

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
    ResourceManager resourceManager;

    Application() = default;
    ~Application() { CloseWindow(); };
    void init(const char* title, int width, int height, unsigned int flags);
    void run();

    void setFPS(unsigned int fps);
private:
    void draw();
};