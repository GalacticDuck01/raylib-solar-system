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

    Star star1 = Star(10.f, 1,  {0.f, 0.f, 0.f}, {0.f, 0.f, -2.f}, RED,  3);
    Star star2 = Star(10.f, 1, {10.f, 0.f, 0.f}, {0.f, 0.f,  2.f}, BLUE, 3);
    
    OrbitalMechanics orbitalMechanics = OrbitalMechanics();
    orbitalMechanics.AddBody(star1);
    orbitalMechanics.AddBody(star2);

    orbitalMechanics.CalcFutureStates(8000);

    float deltaTime = 0.f;
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        deltaTime += GetFrameTime();
        int timeStepsPerFrame = 0;
        float dt = orbitalMechanics.bodies[0]->futurePositions.front().first;
        while (deltaTime >= dt) {
            for (auto& body : orbitalMechanics.bodies) {
                body->futurePositions.pop_front();
            }

            deltaTime -= dt;
            timeStepsPerFrame++;
        orbitalMechanics.Update();
            dt = orbitalMechanics.bodies[0]->futurePositions.front().first;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode3D(camera);


        // Draw lines connecting each upcoming position of each star
        int nStar1Positions = star1.futurePositions.size();
        for (unsigned int is = 0; is < nStar1Positions - 1; is++) {
            Vector3 pos = {star1.futurePositions[is].second.x, star1.futurePositions[is].second.y, star1.futurePositions[is].second.z};
            Vector3 nextPos = {star1.futurePositions[is+1].second.x, star1.futurePositions[is+1].second.y, star1.futurePositions[is+1].second.z};
            float alpha = 1.0f - exp(-(float)is/(0.1f*(float)nStar1Positions));
            DrawLine3D(pos, nextPos, Fade(MAROON, alpha));
        }

        int nStar2Positions = star2.futurePositions.size();
        for (unsigned int is = 0; is < nStar2Positions - 1; is++) {
            Vector3 pos = {star2.futurePositions[is].second.x, star2.futurePositions[is].second.y, star2.futurePositions[is].second.z};
            Vector3 nextPos = {star2.futurePositions[is+1].second.x, star2.futurePositions[is+1].second.y, star2.futurePositions[is+1].second.z};
            float alpha = 1.0f - exp(-(float)is/(0.1f*(float)nStar2Positions));
            DrawLine3D(pos, nextPos, Fade(DARKBLUE, alpha));
        }

        star1.Draw(star1.position, 1.0f, star1.colour);
        star2.Draw(star2.position, 1.0f, star2.colour);

        EndMode3D();

        DrawFPS(10, 100);
        DrawText(TextFormat("deltaTime: %.8f", deltaTime), 10, 30, 20, WHITE);
        DrawText(TextFormat("Steps per frame: %d", timeStepsPerFrame), 400, 30, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}