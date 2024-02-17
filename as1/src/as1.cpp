#ifndef AS1CPP
#define AS1CPP

#include "raylib-cpp.hpp"
#include "raymath.h"
#include <thread>

// Function to translate models using a lambda before drawing
void TranslateAndDraw(raylib::Model& model, const raylib::Vector3& position, const raylib::Vector3& scale, const raylib::Vector3& axis, const float& angle, const raylib::Color& color) {
    model.transform = raylib::Transform(model.transform).Translate(position);
    model.transform = raylib::Transform(model.transform).Scale(scale.x, scale.y, scale.z);
    model.transform = raylib::Transform(model.transform).Rotate(axis, angle);
    DrawModel(model, position, 1.0f, color);

    BoundingBox box = model.GetBoundingBox();
    DrawBoundingBox(box, BLACK);
}

int main() {
    
    raylib::Window window(800, 600, "CS381 - Assignment 1");

    raylib::Model plane = LoadModel("/home/ashton/cs381/as1/381Resources/meshes/PolyPlane.glb");
    plane.transform = raylib::Transform(plane.transform).Scale(3, 3, 3);

    raylib::Model ship = LoadModel("/home/ashton/cs381/as1/381Resources/meshes/SmitHouston_Tug.glb");
    ship.transform = raylib::Transform(ship.transform).RotateXYZ(raylib::Degree(90), 0, raylib::Degree(90));

    raylib::Camera3D camera;
    camera.target = raylib::Vector3(0, 0, 0);
    camera.position = raylib::Vector3(0, 120, -500);
    camera.up = (raylib::Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (raylib::Vector3){0.0f, 0.0f, 0.0f};

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw airplanes and ships with different positions, scales, and rotations
        TranslateAndDraw(plane, {0, 0, 0}, {1, 1, 1}, {0, 0, 0}, 0, {255, 255, 255, 255});  // Default parameters
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TranslateAndDraw(plane, {-100, 100, 0}, {1, -1, 1}, {0, 1, 0}, raylib::Degree(180), {255, 255, 255, 255});
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TranslateAndDraw(ship, {-200, 0, 0}, {1, 1, 1}, {0, 0, 0}, 0, {255, 255, 255, 255});  // Default parameters
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TranslateAndDraw(ship, {200, 0, 0}, {1, 1, 1}, {0, 1, 0}, raylib::Degree(90), {255, 255, 255, 255});
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TranslateAndDraw(ship, {100, 100, 0}, {1, 2, 1}, {0, 1, 0}, raylib::Degree(270), {255, 255, 255, 255});

        EndMode3D();

        EndDrawing();
    }
    CloseWindow();
}
#endif