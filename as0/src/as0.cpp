#ifndef AS0CPP
#define AS0CPP

#include "raylib-cpp.hpp"
#include <string>

void resizeText(){

}

int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    std::string screentitle = "CS 381 - Assignment 0";

    raylib::Window window(screenWidth, screenHeight, screentitle);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    raylib::Color textColor = raylib::Color::LightGray();

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        window.BeginDrawing();
		{
			window.ClearBackground(RAYWHITE);

            textColor.DrawText("HELLO my friend!", 190, 200, 20);

        window.EndDrawing();
        }
    }
    return 0;
}
#endif