#include "raylib.h"

#include "application/application.hpp"
#include "physics/star.hpp"
#include "utils/utils.hpp"

constexpr auto SCREEN_WIDTH  = 1920;
constexpr auto SCREEN_HEIGHT = 1080;

int main() {

    Application app = Application();
    app.init("Window", SCREEN_WIDTH, SCREEN_HEIGHT, FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    std::string windowState = IsWindowMaximized() ? "maximized" : "default";
    log("App initialised with " + windowState + " window size.");
    app.setFPS(60);
    
    Star star = Star({0, 0, 0}, 2, 3);
    app.resourceManager->loadNode("star", star);

    app.run();

    return 0;
}