#include <raylib.h>
#include <Icosphere/Icosphere.hpp>

constexpr auto SCREEN_WIDTH  = 800;
constexpr auto SCREEN_HEIGHT = 450;

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar System");
    SetTargetFPS(60);

    Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };
    Icosphere icosphere;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(10, 1.0f);
        icosphere.Draw();

        EndMode3D();

        EndDrawing();

        
    }

    CloseWindow();
    return 0;
}