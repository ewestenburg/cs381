#include "raylib-cpp.hpp"

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
    position = raylib::Vector3{ 0.0f, 0.0f, 0.0f };
    velocity = raylib::Vector3{ 0.0f, 0.0f, 0.0f };
    return *this;
}


Airplane& Airplane::Update(float deltaTime) {
    // Update airplane's position based on velocity
    position = Vector3Add(position, Vector3Scale(velocity, deltaTime));
    return *this;
}

Airplane& Airplane::Draw() {
    DrawCube(position, 50.0f, 50.0f, 50.0f, RED);  // Draw a simple placeholder cube for the airplane
    return *this;
}

int main() {
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 2");

    raylib::Camera3D camera;
    camera.target = raylib::Vector3(0, 0, 0);
    camera.position = raylib::Vector3(0, 120, -500);
    camera.up = (raylib::Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    SetTargetFPS(60);

    Ground ground;
    ground.Init().LoadTextures("/home/ashton/cs381/as2/381Resources/textures/runway.jpg");

    Airplane airplane;
    airplane.Init();

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        float deltaTime = GetFrameTime();
        UpdateCamera(&camera, CAMERA_FREE);

        // Handle airplane controls
        if (IsKeyDown(KEY_W)) airplane.velocity.z += 5.0f;
        if (IsKeyDown(KEY_S)) airplane.velocity.z -= 5.0f;
        if (IsKeyDown(KEY_A)) airplane.velocity.x -= 5.0f;
        if (IsKeyDown(KEY_D)) airplane.velocity.x += 5.0f;
        if (IsKeyDown(KEY_Q)) airplane.velocity.y += 5.0f;
        if (IsKeyDown(KEY_E)) airplane.velocity.y -= 5.0f;

        // Update airplane physics
        airplane.Update(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw the ground
        ground.Draw();

        // Draw the airplane
        airplane.Draw();

        EndMode3D();

        EndDrawing();
    }

    // Clean up
    CloseWindow();

    return 0;
}