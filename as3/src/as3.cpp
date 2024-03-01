#include "raylib-cpp.hpp"
#include "skybox.hpp"
#include "raymath.h"

class Ground {
public:
    Ground& Init();
    Ground& LoadTextures(const std::string& runwayTexture);
    Ground& Draw();

private:
    Model ground;
    Material runwayMaterial;
};

class Airplane {
public:
    Airplane& Init();
    Airplane& Update(float deltaTime);
    Airplane& Draw();

    raylib::Vector3 position;
    raylib::Vector3 velocity;
    float heading;
    bool isSelected;

    raylib::Model plane;
};

Ground& Ground::Init() {
    // Generate ground plane model
    ground = LoadModelFromMesh(GenMeshPlane(2000.0f, 2000.0f, 1, 1));

    // Initialize runway material
    runwayMaterial = LoadMaterialDefault();
    ground.materials[0] = runwayMaterial;

    return *this;
}

Ground& Ground::LoadTextures(const std::string& runwayTexture) {
    // Load runway texture
    Texture2D runway = LoadTexture(runwayTexture.c_str());

    // Assign texture to runway material
    runwayMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = runway;
    runwayMaterial.maps[MATERIAL_MAP_DIFFUSE].color = WHITE;

    return *this;
}

Ground& Ground::Draw() {
    DrawModel(ground, { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
    return *this;
}

Airplane& Airplane::Init() {
    plane = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane.transform = raylib::Transform(plane.transform).Scale(3, 3, 3);

    position = raylib::Vector3{ 0.0f, 0.0f, 0.0f };
    velocity = raylib::Vector3{ 0.0f, 0.0f, 0.0f };
    return *this;
}


Airplane& Airplane::Update(float deltaTime) {
    // Update airplane's position based on velocity
    position = Vector3Add(position, Vector3Scale(velocity, deltaTime));

    // Update orientation based on heading
    plane.transform = raylib::Transform(plane.transform).RotateY(heading);

    return *this;
}

Airplane& Airplane::Draw() {
    DrawModel(plane, position, 1.0f, RED);
    return *this;
}

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 3");

    raylib::Camera3D camera;
    camera.target = raylib::Vector3(0, 0, 0);
    camera.position = raylib::Vector3(0, 200, -750);
    camera.up = (raylib::Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    SetTargetFPS(60);

    cs381::SkyBox skybox("381Resources/textures/skybox.png");

    Ground ground;
    ground.Init().LoadTextures("381Resources/textures/runway.jpg");

    Airplane airplane1;
    Airplane airplane2;
    Airplane airplane3;
    airplane1.Init();
    airplane2.Init();
    airplane3.Init();

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_TAB)) {
            airplane1.isSelected = !airplane1.isSelected;
            airplane2.isSelected = false;
            airplane3.isSelected = false;
        }   

        // Draw bounding box for the selected airplane
        if (airplane1.isSelected) {
            BoundingBox box = airplane1.plane.GetBoundingBox();
            box.min = Vector3Transform(box.min, airplane1.plane.transform);
            box.max = Vector3Transform(box.max, airplane1.plane.transform);
            DrawBoundingBox(box, BLACK);
        }
        else if (airplane2.isSelected) {
            BoundingBox box = airplane2.plane.GetBoundingBox();
            box.min = Vector3Transform(box.min, airplane2.plane.transform);
            box.max = Vector3Transform(box.max, airplane2.plane.transform);
            DrawBoundingBox(box, BLACK);
        }
        else if (airplane3.isSelected) {
            BoundingBox box = airplane3.plane.GetBoundingBox();
            box.min = Vector3Transform(box.min, airplane3.plane.transform);
            box.max = Vector3Transform(box.max, airplane3.plane.transform);
            DrawBoundingBox(box, BLACK);
        }


        if (airplane1.isSelected) {
        // Handle airplane controls for the selected airplane
            if (IsKeyPressed(KEY_W)) airplane1.velocity.z += 5.0f;
            if (IsKeyPressed(KEY_S)) airplane1.velocity.z -= 5.0f;
            if (IsKeyPressed(KEY_A)) airplane1.heading += 2.0f;
            if (IsKeyPressed(KEY_D)) airplane1.heading -= 2.0f;
            if (IsKeyPressed(KEY_SPACE)) airplane1.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
        }

        if (airplane2.isSelected) {
        // Handle airplane controls for the selected airplane
            if (IsKeyPressed(KEY_W)) airplane2.velocity.z += 5.0f;
            if (IsKeyPressed(KEY_S)) airplane2.velocity.z -= 5.0f;
            if (IsKeyPressed(KEY_A)) airplane2.heading += 2.0f;
            if (IsKeyPressed(KEY_D)) airplane2.heading -= 2.0f;
            if (IsKeyPressed(KEY_SPACE)) airplane2.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
        }

        if (airplane3.isSelected) {
        // Handle airplane controls for the selected airplane
            if (IsKeyPressed(KEY_W)) airplane3.velocity.z += 5.0f;
            if (IsKeyPressed(KEY_S)) airplane3.velocity.z -= 5.0f;
            if (IsKeyPressed(KEY_A)) airplane3.heading += 2.0f;
            if (IsKeyPressed(KEY_D)) airplane3.heading -= 2.0f;
            if (IsKeyPressed(KEY_SPACE)) airplane3.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
        }

        //Camera held still
        //UpdateCamera(&camera, CAMERA_FREE);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw the skybox
        skybox.Draw();

        // Draw the ground
        ground.Draw();

        // Draw the airplane
        airplane1.Draw();
        airplane2.Draw();
        airplane3.Draw();

        EndMode3D();

        EndDrawing();
    }

    // Clean up
    CloseWindow();

    return 0;
}