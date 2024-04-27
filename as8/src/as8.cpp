#include <raylib-cpp.hpp>

#include <memory>
#include <ranges>
#include <iostream>
#include <array>
#include <cstddef>
#include <vector>
#include <cassert>

#include "skybox.hpp"

using Entity = uint8_t;

// Define components
struct Position {
    raylib::Vector3 value;
};

struct Speed {
    float value;
};

struct Heading {
    raylib::Degree value;
};

// ComponentStorage to store components
struct ComponentStorage {
    size_t elementSize = -1;
    std::vector<std::byte> data;

    ComponentStorage() : elementSize(-1), data(1, std::byte{0}) {}
    ComponentStorage(size_t elementSize) : elementSize(elementSize) {data.resize(5 * elementSize); }
    
    template<typename Tcomponent>
    ComponentStorage(Tcomponent reference = {}) : ComponentStorage(sizeof(Tcomponent)) {}

    template<typename Tcomponent>
    Tcomponent& Get(Entity e) {
        assert(sizeof(Tcomponent) == elementSize);
        assert(e < data.size() / elementSize);
        return *(Tcomponent*)(data.data() + e * elementSize);
    }

    template<typename Tcomponent>
    std::pair<Tcomponent&, Entity> Allocate(size_t count = 1) {
        assert(sizeof(Tcomponent) == elementSize);
        assert(count < 255);
        auto originalEnd = data.size();
        data.insert(data.end(), elementSize * count, std::byte{0});
        for(size_t i = 0; i < count - 1; i++) {
            new(data.data() + originalEnd + i * elementSize) Tcomponent();
        }
        return {
            *reinterpret_cast<Tcomponent*>(data.data() + data.size() - elementSize),
            data.size() / elementSize
        };
    }

    template<typename Tcomponent>
    Tcomponent& GetOrAllocate(Entity e) {
        assert(sizeof(Tcomponent) == elementSize);
        size_t size = data.size() / elementSize;
        if (size <= e){
            Allocate<Tcomponent>(std::max<int64_t>(int64_t(e), size) - size + 1);
        }
        return Get<Tcomponent>(e);
    }
};

// Define entity IDs
enum PlaneEntities : Entity {
    plane0,
    plane1,
    plane2
};

// Global component storages
ComponentStorage positionStorage(sizeof(Position));
ComponentStorage speedStorage(sizeof(Speed));
ComponentStorage headingStorage(sizeof(Heading));

// Transformer concept
template<typename T>
concept Transformer = requires(T t, raylib::Transform m) {
	{ t.operator()(m) } -> std::convertible_to<raylib::Transform>;
};

// CalculateVelocityParams structure
struct CalculateVelocityParams {
    static constexpr float acceleration = 5;
    static constexpr float angularAcceleration = 15;

    std::array<raylib::Vector3, 10> position;
    std::array<float, 10> targetSpeed;
    std::array<raylib::Degree, 10> targetHeading;
};

bool ProcessInput(ComponentStorage& speedStorage, ComponentStorage& headingStorage, size_t selectedPlane) {
    // Update speed and heading based on input
    Speed& speed = speedStorage.GetOrAllocate<Speed>(selectedPlane);
    Heading& heading = headingStorage.GetOrAllocate<Heading>(selectedPlane);

    // Similar input handling code as before, modifying speed.value and heading.value
    // For example:
    if (IsKeyDown(KEY_W))
        speed.value += 1;
    if (IsKeyDown(KEY_A))
        heading.value += raylib::Degree(5);

    // Handle plane selection
    if (IsKeyPressed(KEY_TAB))
        selectedPlane = (selectedPlane + 1) % 3;

    return !IsKeyDown(KEY_ESCAPE);
}


// CalculateVelocity function
raylib::Vector3 CalculateVelocity(const CalculateVelocityParams& data) {
    // Implement velocity calculation using data from CalculateVelocityParams
	return {0, 0, 0};
}

// DrawBoundedModel function
void DrawBoundedModel(raylib::Model& model, Entity planeEntity) {
    // Retrieve position and heading from ComponentStorage for the given plane entity
    Position& position = positionStorage.GetOrAllocate<Position>(planeEntity);
    Heading& heading = headingStorage.GetOrAllocate<Heading>(planeEntity);

    // Define a transformer based on the retrieved position and heading
    auto transformer = [&](raylib::Transform transform) {
        return transform.Translate(position.value).RotateY(heading.value);
    };

    // Draw the model with bounding box
    raylib::Transform backupTransform = model.transform;
    model.transform = transformer(backupTransform);
    model.Draw({});
    model.GetTransformedBoundingBox().Draw();
    model.transform = backupTransform;
}

// DrawModel function
void DrawModel(raylib::Model& model, Entity planeEntity) {
    // Retrieve position and heading from ComponentStorage for the given plane entity
    Position& position = positionStorage.GetOrAllocate<Position>(planeEntity);
    Heading& heading = headingStorage.GetOrAllocate<Heading>(planeEntity);

    // Define a transformer based on the retrieved position and heading
    auto transformer = [&](raylib::Transform transform) {
        return transform.Translate(position.value).RotateY(heading.value);
    };

    // Draw the model
    raylib::Transform backupTransform = model.transform;
    model.transform = transformer(backupTransform);
    model.Draw({});
    model.transform = backupTransform;
}

void UpdatePhysics(Entity entity, ComponentStorage& positionStorage, ComponentStorage& speedStorage, ComponentStorage& headingStorage, float deltaTime) {
    Position& position = positionStorage.GetOrAllocate<Position>(entity);
    const Speed& speed = speedStorage.Get<Speed>(entity);
    const Heading& heading = headingStorage.Get<Heading>(entity);

    raylib::Vector3 velocity = {
        cos(heading.value) * speed.value,
        0,  // Assuming movement is only in the XZ plane
        sin(heading.value) * speed.value
    };

    position.value += velocity * deltaTime;
}

int main() {
    // Create window
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;
    raylib::Window window(screenWidth, screenHeight, "CS381 - Assignment 8");

	raylib::Model plane = LoadModel("381Resources/meshes/PolyPlane.glb");

	// Define variables for plane 0
	raylib::Vector3 plane0Position = {0.0f, 0.0f, 0.0f};
	raylib::Vector3 plane0Velocity = {0.0f, 0.0f, 0.0f};
	raylib::Degree plane0TargetHeading = 0.0f;
	float plane0TargetSpeed = 0.0f;

	// Define variables for plane 1
	raylib::Vector3 plane1Position = {0.0f, 0.0f, 0.0f};
	raylib::Vector3 plane1Velocity = {0.0f, 0.0f, 0.0f};
	raylib::Degree plane1TargetHeading = 0.0f;
	float plane1TargetSpeed = 0.0f;

	// Define variables for plane 2
	raylib::Vector3 plane2Position = {0.0f, 0.0f, 0.0f};
	raylib::Vector3 plane2Velocity = {0.0f, 0.0f, 0.0f};
	raylib::Degree plane2TargetHeading = 0.0f;
	float plane2TargetSpeed = 0.0f;

    
    size_t selectedPlane = 0;

    // Main loop
    bool keepRunning = true;
    while(!window.ShouldClose() && keepRunning) {
        // Updates
        if (!ProcessInput(speedStorage, headingStorage, selectedPlane))
            break;

        // Physics update for each entity
        float deltaTime = window.GetFrameTime();
        for (Entity e = plane0; e <= plane2; e++) {
            UpdatePhysics(e, positionStorage, speedStorage, headingStorage, deltaTime);
        }

		// Create camera
		auto camera = raylib::Camera(
			raylib::Vector3(0, 120, -500), // Position
			raylib::Vector3(0, 0, 300), // Target
			raylib::Vector3::Up(), // Up direction
			45.0f,
			CAMERA_PERSPECTIVE
		);

		// Create skybox
		cs381::SkyBox skybox("381Resources/textures/skybox.png");

		// Create ground
		auto mesh = raylib::Mesh::Plane(10000, 10000, 50, 50, 25);
		raylib::Model ground = ((raylib::Mesh*)&mesh)->LoadModelFrom();
		raylib::Texture grass("381Resources/textures/grass.jpg");
		grass.SetFilter(TEXTURE_FILTER_BILINEAR);
		grass.SetWrap(TEXTURE_WRAP_REPEAT);
		ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grass;


        // Rendering
        window.BeginDrawing();
        {
            // Clear screen
			window.ClearBackground(BLACK);

			camera.BeginMode();
			{
				// Render skybox and ground
				skybox.Draw();
				ground.Draw({});

				// Draw the planes with a bounding box around the selected plane
				switch(selectedPlane) {
					break; case 0: {
						DrawBoundedModel(plane, plane0);
						DrawModel(plane, plane1);
						DrawModel(plane, plane2);
					} break; case 1: {
						DrawModel(plane, plane0);
						DrawBoundedModel(plane, plane1);
						DrawModel(plane, plane2);
					} break; case 2: {
						DrawModel(plane, plane0);
						DrawModel(plane, plane1);
						DrawBoundedModel(plane, plane2);
					}
				}
			}
			camera.EndMode();

			// Measure our FPS
			DrawFPS(10, 10);
		}
		window.EndDrawing();
    }

    return 0;
}