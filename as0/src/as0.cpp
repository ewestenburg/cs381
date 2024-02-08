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
    AnimateText();
}

void SimpleWindow::Draw() {
    window.BeginDrawing();
    {
        window.ClearBackground(RAYWHITE);

        textColor.DrawText(displayText.c_str(), textPosition.x, textPosition.y + textOffset, textSize);
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

void SimpleWindow::AnimateText() {
    // moves text up and down
    textOffset += 1.0f;

    if (textOffset > 20.0f) {
        textOffset = -20.0f;
    }

    // changes color
    float hue = fmod(GetTime() * 100, 360.0f);
    textColor = ColorFromHSV(hue, 0.8f, 0.8f);
    textColor2 = ColorFromHSV(hue + 180.0f, 0.8f, 0.8f);
}


int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SimpleWindow simplewindow;
    simplewindow.Run();

    return 0;
}
#endif