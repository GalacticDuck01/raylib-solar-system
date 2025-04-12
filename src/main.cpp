#include <raylib.h>
#include <Star.hpp>
#include <Operators/OrbitalMechanics/OrbitalMechanics.hpp>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Solar System");
    SetTargetFPS(60);
    ToggleFullscreen();

    DisableCursor();

    Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    Star star1 = Star(10.f, 1, { 0.f, 0.f, -10.f}, {0.f, 0.f, 0.f}, RED,    3);
    Star star2 = Star(10.f, 1, {-10.f, 0.f,  0.f}, {0.f, 0.f, 0.f}, BLUE,   3);
    Star star3 = Star(10.f, 1, { 0.f, 0.f,  10.f}, {0.f, 0.f, 0.f}, GREEN,  3);
    Star star4 = Star(10.f, 1, { 10.f, 0.f,  0.f}, {0.f, 0.f, 0.f}, YELLOW, 3);

    star1.velocity = (star2.position - star1.position).normalised()*4.f;
    star2.velocity = (star3.position - star2.position).normalised()*4.f;
    star3.velocity = (star4.position - star3.position).normalised()*4.f;
    star4.velocity = (star1.position - star4.position).normalised()*4.f;
    
    OrbitalMechanics orbitalMechanics = OrbitalMechanics();
    orbitalMechanics.AddBody(star1);
    orbitalMechanics.AddBody(star2);
    orbitalMechanics.AddBody(star3);
    orbitalMechanics.AddBody(star4);

    orbitalMechanics.CalcFutureStates(2e5);

    bool isPaused = true;
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed(KEY_P)) isPaused = !isPaused;
        if (!isPaused) {
            if (GetFrameTime() != 0.f) orbitalMechanics.RenderUpdate(GetFrameTime());
        }

        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawGrid(30, 1.0f);

        orbitalMechanics.DrawTrajectories(10000);

        star1.Draw(star1.futurePositions[0].second, 1.0f, star1.colour);
        star2.Draw(star2.futurePositions[0].second, 1.0f, star2.colour);
        star3.Draw(star3.futurePositions[0].second, 1.0f, star3.colour);
        star4.Draw(star4.futurePositions[0].second, 1.0f, star4.colour);

        EndMode3D();

        DrawFPS(10, 100);
        DrawText(TextFormat("deltaTime: %.8f", GetFrameTime()), 10, 30, 20, WHITE);
        DrawText(TextFormat("Steps per frame: %d", orbitalMechanics.GetStepsPerUpdate()), 400, 30, 20, WHITE);
        DrawText(TextFormat("dt: %.8f", GetFrameTime()/orbitalMechanics.GetStepsPerUpdate()), 700, 30, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}