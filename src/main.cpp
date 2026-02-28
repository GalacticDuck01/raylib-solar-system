#include "raylib.h"

#include "application/application.hpp"
#include "utils/utils.hpp"

constexpr auto SCREEN_WIDTH  = 1920;
constexpr auto SCREEN_HEIGHT = 1080;

int main() {

    Application app = Application();
    app.init("Window", SCREEN_WIDTH, SCREEN_HEIGHT, FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_RESIZABLE);
    std::string windowState = IsWindowMaximized() ? "maximized" : "default";
    log("App initialised with " + windowState + " window size.");
    app.setFPS(60);
    app.run();

    return 0;
}