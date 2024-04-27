#include <raylib-cpp.hpp>

#include <memory>
#include <ranges>
#include <iostream>
#include <array>
#include <cstddef>
#include <vector>
#include <cassert>
#include <algorithm>

#include "skybox.hpp"

using Entity = uint8_t;

// Components
struct TransformComponent {
    raylib::Vector3 position;
    raylib::Quaternion rotation;  // Used for 3D physics
    float yaw;  // Used for 2D physics
};

struct Kinematics {
    raylib::Vector3 velocity;
    float speed;
    float maxSpeed;
    float acceleration;
};

struct RenderComponent {
    raylib::Model model;
    bool drawBoundingBox;
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
enum Entities : Entity {
    plane0,
    plane1,
    plane2,
	plane3,
	plane4,
	ship0,
	ship1,
	ship2,
	ship3,
	ship4
};

// Global component storages
ComponentStorage transformStorage(sizeof(TransformComponent));
ComponentStorage kinematicsStorage(sizeof(Kinematics));
ComponentStorage renderStorage(sizeof(RenderComponent));

void InitializeComponents() {
	// Allocate storage for each component type based on expected number of entities
	size_t numEntities = 5;  // Example for 5 ships and 5 planes
	transformStorage.Allocate<TransformComponent>(numEntities * 2);
	kinematicsStorage.Allocate<Kinematics>(numEntities * 2);
	renderStorage.Allocate<RenderComponent>(numEntities * 2);
}

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
    TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(selectedPlane);
    Kinematics& kinematics = kinematicsStorage.GetOrAllocate<Kinematics>(selectedPlane);


    // Similar input handling code as before, modifying speed.value and heading.value
    // For example:
    if (IsKeyDown(KEY_W))
        kinematics.speed += 1;
    if (IsKeyDown(KEY_A))
        // Assuming transform.rotation is a raylib::Quaternion
		transform.rotation = QuaternionMultiply(transform.rotation, QuaternionFromAxisAngle(raylib::Vector3{0, 1, 0}, 5 * DEG2RAD));


    // Handle plane selection
    if (IsKeyPressed(KEY_TAB))
        selectedPlane = (selectedPlane + 1) % 10;

    return !IsKeyDown(KEY_ESCAPE);
}


// CalculateVelocity function
raylib::Vector3 CalculateVelocity(const CalculateVelocityParams& data) {
    // Implement velocity calculation using data from CalculateVelocityParams
	return {0, 0, 0};
}

// DrawBoundedModel function
void DrawBoundedModel(raylib::Model& model, Entity planeEntity) {
    TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(planeEntity);

    // Convert quaternion rotation to Matrix and apply translation
    raylib::Matrix matRotation = QuaternionToMatrix(transform.rotation);
    raylib::Matrix matTranslation = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);
    raylib::Matrix transformMatrix = MatrixMultiply(matRotation, matTranslation);

    // Set the model transform, draw the model and bounding box
    raylib::Transform backupTransform = model.transform;
    model.transform = transformMatrix;
    model.Draw({});
    model.GetTransformedBoundingBox().Draw();
    model.transform = backupTransform;
}


// DrawModel function
void DrawModel(raylib::Model& model, Entity planeEntity) {
    TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(planeEntity);

    // Convert quaternion rotation to Matrix and apply translation
    raylib::Matrix matRotation = QuaternionToMatrix(transform.rotation);
    raylib::Matrix matTranslation = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);
    raylib::Matrix transformMatrix = MatrixMultiply(matRotation, matTranslation);

    // Set the model transform and draw
    raylib::Transform backupTransform = model.transform;
    model.transform = transformMatrix;
    model.Draw({});
    model.transform = backupTransform;
}

void UpdatePhysics(ComponentStorage& transformStorage, ComponentStorage& kinematicsStorage, float deltaTime) {
    for (Entity e = 0; e < 10; e++) {
        TransformComponent& transform = transformStorage.Get<TransformComponent>(e);
        Kinematics& kinematics = kinematicsStorage.Get<Kinematics>(e);

        // Update the position based on velocity
        transform.position += kinematics.velocity * deltaTime;

        // If additional rotational dynamics are involved:
        // Example: Update yaw, which could be used for 2D elements in a 3D world (like ships)
        // This would require converting the yaw changes into a quaternion and applying it to rotation
        if (std::abs(kinematics.acceleration) > 0.001f) {  // Check if there's meaningful acceleration
            kinematics.speed += kinematics.acceleration * deltaTime;
            if (kinematics.speed < 0.0f) {
				kinematics.speed = 0.0f;
			} else if (kinematics.speed > kinematics.maxSpeed) {
				kinematics.speed = kinematics.maxSpeed;
			}
        }

        // Update the velocity based on speed and direction (assuming yaw is the direction in 2D)
        kinematics.velocity = raylib::Vector3{
            cos(transform.yaw * DEG2RAD) * kinematics.speed,  // X component
            0,  // Y component, assuming no vertical movement
            sin(transform.yaw * DEG2RAD) * kinematics.speed   // Z component
        };
    }
}

int main() {
    // Create window
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;
    raylib::Window window(screenWidth, screenHeight, "CS381 - Assignment 8");

	raylib::Model plane = LoadModel("381Resources/meshes/PolyPlane.glb");

	InitializeComponents();

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
        if (!ProcessInput(transformStorage, kinematicsStorage, selectedPlane))
            break;

        // Physics update for each entity
        float deltaTime = window.GetFrameTime();
        for (Entity e = plane0; e <= plane2; e++) {
            UpdatePhysics(transformStorage, kinematicsStorage, deltaTime);
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
		raylib::Texture water("381Resources/textures/water.jpg");
		water.SetFilter(TEXTURE_FILTER_BILINEAR);
		water.SetWrap(TEXTURE_WRAP_REPEAT);
		ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = water;


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