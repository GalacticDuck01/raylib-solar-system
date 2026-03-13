#include "raylib.h"

#include "application/application.hpp"
#include "physics/star.hpp"
#include "utils/utils.hpp"

constexpr auto SCREEN_WIDTH  = 1920;
constexpr auto SCREEN_HEIGHT = 1080;

int main() {

    Application app = Application();
    app.init("Window", SCREEN_WIDTH, SCREEN_HEIGHT, FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    app.setFPS(600);
    
    Star star = Star({0, 0, 0}, 2, 4);
    star.setFlatShading(true);
    Star planet = Star({5, 0, 0}, 1, 3);
    planet.setTint(BLUE);
    planet.setFlatShading(true);
    app.entityManager->loadEntity("star", star);
    app.entityManager->loadEntity("planet", planet);

    app.run();

    return 0;
}
