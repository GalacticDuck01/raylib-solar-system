#include "application.hpp"

#include "raylib.h"

#include "utils/utils.hpp"

void Application::init(const char* title, int width, int height, unsigned int flags) {
    log("[Raylib] Initialising window...");

    // Initialise window
    SetConfigFlags(flags);
    InitWindow(width, height, title);

    // Raylib doesn't support maximisation on initialisation on desktop GLFW, so we have to do it manually here.
    if ((flags & FLAG_WINDOW_MAXIMIZED) != 0) {
        MaximizeWindow();
    }

    SetExitKey(KEY_NULL);
    int targetFPS = GetMonitorRefreshRate(GetCurrentMonitor());
    log("[Raylib] Setting target FPS to " + std::to_string(targetFPS));
    SetTargetFPS(targetFPS);

    // Initialise audio
    InitAudioDevice();
    log("[Raylib] Initialisation finished");
}

void Application::run() {
    log("Entering main loop...");
    state = AppState::LOADING;
    // TODO: Load assets here, then switch to menu or running state
    state = AppState::RUNNING;

    while (state != AppState::QUITTING) {
        switch (state) {
            case AppState::LOADING:
                // TODO: Load assets
                break;
            case AppState::MENU:
                // TODO: Menu
                break;
            case AppState::PAUSED:
                // TODO: Paused
                break;
            case AppState::RUNNING:
                draw();
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

void Application::draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    const char* text = "YARRR!";
    const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
    DrawText(text, 0, 0, 20, BLACK);

     BeginMode3D(camera);
        DrawGrid(10, 1.0f);
        resourceManager->render();
     EndMode3D();

     DrawFPS(10, 10);

     DrawText("Hello, world!", 10, 40, 20, DARKGRAY);

     log("Drawing frame...");

    EndDrawing();
}