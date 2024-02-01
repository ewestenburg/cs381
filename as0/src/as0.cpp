#ifndef AS0CPP
#define AS0CPP

#include "as0.hpp"
#include <iostream>

SimpleWindow::SimpleWindow() : window(800, 450, "CS381 - Assignment 0"), windowTitle("CS381 - Assignment 0")
                            ,textColor(raylib::Color::LightGray()),
                            displayText("Hello there!"), textSize(20), textPosition(raylib::Vector2{0}) {
    Initialize();
}

SimpleWindow::~SimpleWindow() {
    CloseWindow();
}

void SimpleWindow::Initialize() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    ResizeText();
}

void SimpleWindow::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void SimpleWindow::Update() {
    if (IsWindowResized()) {
        ResizeText();
    }
}

void SimpleWindow::Draw() {
    window.BeginDrawing();
    {
        window.ClearBackground(RAYWHITE);

        textColor.DrawText(displayText.c_str(), textPosition.x, textPosition.y, textSize);
    }
    window.EndDrawing();
}

void SimpleWindow::ResizeText() {
    // text width and height
    float textWidth = MeasureText(displayText.c_str(), textSize);
    float textHeight = static_cast<float>(textSize);

    // center text 
    textPosition.x = static_cast<float>(window.GetWidth() / 2 - textWidth / 2);
    textPosition.y = static_cast<float>(window.GetHeight() / 2 - textHeight / 2);
}

int main() {
    SimpleWindow simplewindow;
    simplewindow.Run();

    return 0;
}
#endif