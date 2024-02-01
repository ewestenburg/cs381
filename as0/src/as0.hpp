#ifndef AS0HPP
#define AS0HPP

#include "raylib-cpp.hpp"
#include <string>

class SimpleWindow{
public:
    SimpleWindow();
    ~SimpleWindow();

    void Run();

private:
    void Initialize();
    void Update();
    void Draw();
    void ResizeText();

    raylib::Window window;
    std::string windowTitle;
    raylib::Color textColor;
    raylib::Color textColor2;

    std::string displayText;
    int textSize;
    raylib::Vector2 textPosition;
};
#endif