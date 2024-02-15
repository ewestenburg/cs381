#ifndef AS1CPP
#define AS1CPP

#include "raylib-cpp.hpp"

int main() {
    raylib::Window window(800, 600, "CS381 - Assignment 1");

    raylib::Model plane = LoadModel("/home/ashton/cs381/as1/381Resources/meshes/PolyPlane.glb");
    plane.transform = raylib::Transform(plane.transform).Scale(3, 3, 3);

    raylib::Model ship = LoadModel("/home/ashton/cs381/as1/381Resources/meshes/OilTanker.glb");
    ship.transform = raylib::Transform(ship.transform).RotateXYZ(raylib::Degree(90), 0, raylib::Degree(90));

    raylib::Camera3D camera;
    camera.target = raylib::Vector3(0, 0, 0);
    camera.position = raylib::Vector3(100, 100, 100);
    camera.up = raylib::Vector3::Up();
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    DisableCursor();

    // Main game loop
    while (!WindowShouldClose())       
    {
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                plane.Draw({0, 1, 0}, 1.0f, {255, 255, 255, 255});

            EndMode3D();

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

        EndDrawing();

    }
    CloseWindow();
}
#endif
