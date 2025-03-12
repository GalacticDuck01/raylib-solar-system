#include <raylib.h>
#include <Star.hpp>
#include <Operators/OrbitalMechanics/OrbitalMechanics.hpp>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Solar System");
    SetTargetFPS(60);
    // ToggleFullscreen();

    DisableCursor();

    Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    Star star1 = Star(RED, 5);
    star1.position = { 0.f, 0.f, 0.f };
    star1.velocity = { 0.f, 0.f, -2.f };
    star1.mass = 10.f;
    Star star2 = Star(BLUE, 5);
    star2.position = { 10.f, 0.f, 0.f };
    star2.velocity = { 0.f, 0.f, 2.f };
    star2.mass = 10.f;
    
    OrbitalMechanics orbitalMechanics = OrbitalMechanics();
    orbitalMechanics.AddBody(star1);
    orbitalMechanics.AddBody(star2);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        orbitalMechanics.Update();
        star1.Update(1.0f/60.0f);
        star2.Update(1.0f/60.0f);

        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(100, 1.0f);
        star1.Draw(star1.position, 1.0f, star1.colour);
        star2.Draw(star2.position, 1.0f, star2.colour);

        EndMode3D();

        EndDrawing();

        
    }

    CloseWindow();
    return 0;
}