#include "application.hpp"

#include "raylib.h"

#include "utils/utils.hpp"

void Application::init(const char* title, int width, int height, unsigned int flags) {
    log("[Raylib] Initialising window...");

    // Initialise window
    SetConfigFlags(flags);
    InitWindow(width, height, title);
    SetTraceLogLevel(LOG_WARNING); // Only log warnings and errors from raylib

    // Raylib doesn't support maximisation on initialisation on desktop GLFW, so we have to do it manually here.
    if ((flags & FLAG_WINDOW_MAXIMIZED) != 0) {
        MaximizeWindow();
        log("[Raylib] Maximized window");
    }

    SetExitKey(KEY_NULL);
    int targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
    log("[Raylib] Matching monitor refresh rate: " + std::to_string(targetFPS) + " FPS");
    SetTargetFPS(targetFPS);

    // Initialise audio
    InitAudioDevice();

    // Initialise camera
    cameraSystem->initialise();

    // Initialise shader
    shader = LoadShader("shaders/phong_vertex.glsl", "shaders/phong_fragment.glsl");

    log("[Raylib] Initialisation finished");
}

void Application::run() {
    state = AppState::LOADING;
    // TODO: Load assets here, then switch to menu or running state
    state = AppState::RUNNING;

    while (state != AppState::QUITTING) {
        switch (state) {
            case AppState::LOADING:
                // TODO: Load assets
                break;
            case AppState::MENU:
                menuUpdate();
                break;
            case AppState::PAUSED:
                // TODO: Paused
                break;
            case AppState::RUNNING:
                runUpdate();
                render();
                break;
            case AppState::GAME_OVER:
                // TODO: Game over
                break;
            default:
                break;
        }

        if (WindowShouldClose()) {
            state = AppState::QUITTING;
        }
    }
}

void Application::setFPS(unsigned int fps) {
    SetTargetFPS(fps);
}

void Application::menuUpdate() {
}

void Application::runUpdate() {
    cameraSystem->update();
    cameraSystem->sendToShader(shader);
}

void Application::render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    Vector3 lightPos = { -10.0f, 10.0f, 1.0f };
    SetShaderValue(shader, GetShaderLocation(shader, "lightPosition"), &lightPos, SHADER_UNIFORM_VEC3);

    const char* text = "YARRR!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, 0, 0, 20, BLACK);

    cameraSystem->beginMode3D();
    DrawGrid(10, 1.0f);
    entityManager->render(shader);
    cameraSystem->endMode3D();

     DrawFPS(10, 10);

     DrawText("Hello, world!", 10, 40, 20, DARKGRAY);

    EndDrawing();
}
