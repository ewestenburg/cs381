#ifndef AS0HPP
#define AS0HPP

#include "raylib-cpp.hpp"
#include <string>

class Assignment {
public:
    Assignment();
    ~Assignment();

    void Run();

private:
    void Initialize();
    void Update();
    void Draw();
    void ResizeText();

    static void ResizeCallback(int width, int height);

    raylib::Window window;
    std::string windowTitle;
    bool resizable;
    raylib::Color textColor;

    std::string displayText;
    int textSize;
    raylib::Vector2 textPosition;
};

#endif // AS0_HPP
