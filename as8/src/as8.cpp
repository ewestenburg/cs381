#include <raylib-cpp.hpp>

#include <memory>
#include <ranges>
#include <iostream>
#include <array>
#include <cstddef>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <BufferedInput.hpp>

#include "skybox.hpp"

using Entity = uint8_t;

// Components
struct TransformComponent {
    raylib::Vector3 position;
    raylib::Quaternion rotation;  
    float yaw; 
};

struct Kinematics {
    raylib::Vector3 velocity = {0.0, 0.0, 0.0};
    float speed = 0.0;
    float maxSpeed;
    float acceleration;
	bool shouldAccelerate = false;
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

// Entity IDs
enum Entities : Entity {
	ship0,
	ship1,
	ship2,
	ship3,
	ship4,
	plane0,
    plane1,
    plane2,
	plane3,
	plane4
};

// Global component storages
ComponentStorage transformStorage(sizeof(TransformComponent));
ComponentStorage kinematicsStorage(sizeof(Kinematics));
ComponentStorage renderStorage(sizeof(RenderComponent));
int selectedEntity = 0;

void InitializeComponents() {
	size_t numEntities = 5;  //for 5 ships and 5 planes
	transformStorage.Allocate<TransformComponent>(numEntities * 2);
	kinematicsStorage.Allocate<Kinematics>(numEntities * 2);
	renderStorage.Allocate<RenderComponent>(numEntities * 2);
}

void InitializeScene() {
    for (int i = 0; i < 5; i++) {
        Entity ship = static_cast<Entity>(ship0 + i);

        // Initialize ships
        TransformComponent& shipTransform = transformStorage.GetOrAllocate<TransformComponent>(ship);
        shipTransform.position = raylib::Vector3{ -100.0f * i, 0.0f, 100.0f * i };
        shipTransform.yaw = -90.0f; 

        Kinematics& shipKinematics = kinematicsStorage.GetOrAllocate<Kinematics>(ship);
		shipKinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f}; // Explicitly set initial velocity to zero
        shipKinematics.speed = 0.0f; // Explicitly set initial speed to zero
        shipKinematics.maxSpeed = 20.0f + 10.0f * i; // Each ship has different max speed
        shipKinematics.acceleration = 2.0f + 1.0f * i; // Different acceleration
    }

	for (int i = 0; i < 5; i++) {
		Entity plane = static_cast<Entity>(plane0 + i);

        TransformComponent& planeTransform = transformStorage.GetOrAllocate<TransformComponent>(plane);
        planeTransform.position = raylib::Vector3{ -100.0f * i, 200.0f, 100.0f * i }; // Directly above ships
        planeTransform.rotation = QuaternionFromEuler(0, 0.0f * DEG2RAD, 0); // Facing right

        Kinematics& planeKinematics = kinematicsStorage.GetOrAllocate<Kinematics>(plane);
		planeKinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f}; // Explicitly set initial velocity to zero
        planeKinematics.speed = 0.0f; // Explicitly set initial speed to zero
        planeKinematics.maxSpeed = 50.0f + 20.0f * i; 
        planeKinematics.acceleration = 5.0f + 2.0f * i;
	}
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

raylib::Vector3 CalculateVelocity(const CalculateVelocityParams& data, size_t entityIndex) {
	if (entityIndex >= data.targetSpeed.size()) {
		return {0, 0, 0};
	}

	float speed = data.targetSpeed[entityIndex];
	float headingInRadians = static_cast<float>(data.targetHeading[entityIndex]) * (M_PI / 180.0f);

	float vx = speed * cos(headingInRadians);
	float vz = speed * sin(headingInRadians);

	return {vx, 0, vz};
}

// DrawBoundedModel function
void DrawBoundedModel(raylib::Model& model, Entity planeEntity) {
    TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(planeEntity);

    raylib::Matrix matRotation = QuaternionToMatrix(transform.rotation);
    raylib::Matrix matTranslation = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);
    raylib::Matrix transformMatrix = MatrixMultiply(matRotation, matTranslation);

    raylib::Transform backupTransform = model.transform;
    model.transform = transformMatrix;
    model.Draw({});
    model.GetTransformedBoundingBox().Draw();
    model.transform = backupTransform;
}


// DrawModel function
void DrawModel(raylib::Model& model, Entity planeEntity) {
    TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(planeEntity);

    raylib::Matrix matRotation = QuaternionToMatrix(transform.rotation);
    raylib::Matrix matTranslation = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);
    raylib::Matrix transformMatrix = MatrixMultiply(matRotation, matTranslation);

    // Set the model transform and draw
    raylib::Transform backupTransform = model.transform;
    model.transform = transformMatrix;
    model.Draw({});
    model.transform = backupTransform;
}

void Update2DPhysics(ComponentStorage& transformStorage, ComponentStorage& kinematicsStorage, float deltaTime) {
    for (Entity e = ship0; e <= ship4; e++) {
        TransformComponent& transform = transformStorage.Get<TransformComponent>(e);
        Kinematics& kinematics = kinematicsStorage.Get<Kinematics>(e);

        // Apply acceleration only if shouldAccelerate is true
        if (kinematics.shouldAccelerate && std::abs(kinematics.acceleration) > 0.001f) {
            kinematics.speed += kinematics.acceleration * deltaTime;
            if (kinematics.speed < 0.0f) {
				kinematics.speed = 0.0f;
			} else if (kinematics.speed > kinematics.maxSpeed) {
				kinematics.speed = kinematics.maxSpeed;
			}
        }

        kinematics.velocity = raylib::Vector3{
            cos(transform.yaw * DEG2RAD) * kinematics.speed,
            0,
            sin(transform.yaw * DEG2RAD) * kinematics.speed
        };

        transform.position += kinematics.velocity * deltaTime;
    }
}

void Update3DPhysics(ComponentStorage& transformStorage, ComponentStorage& kinematicsStorage, float deltaTime) {
    for (Entity e = plane0; e <= plane4; e++) {
        TransformComponent& transform = transformStorage.Get<TransformComponent>(e);
        Kinematics& kinematics = kinematicsStorage.Get<Kinematics>(e);

        // Apply acceleration only if shouldAccelerate is true
        if (kinematics.shouldAccelerate && std::abs(kinematics.acceleration) > 0.001f) {
            kinematics.speed += kinematics.acceleration * deltaTime;
            if (kinematics.speed < 0.0f) {
                kinematics.speed = 0.0f;
            } else if (kinematics.speed > kinematics.maxSpeed) {
                kinematics.speed = kinematics.maxSpeed;
            }
        }

        raylib::Vector3 forward = Vector3RotateByQuaternion(raylib::Vector3{0, 0, 1}, transform.rotation);
        kinematics.velocity = forward * kinematics.speed;

        transform.position += kinematics.velocity * deltaTime;
    }
}

raylib::Matrix MatrixFromTransformComponent(const TransformComponent& transform) {
    raylib::Matrix rotationMatrix = QuaternionToMatrix(transform.rotation);
    raylib::Matrix translationMatrix = MatrixTranslate(transform.position.x, transform.position.y, transform.position.z);

    raylib::Matrix transformMatrix = MatrixMultiply(rotationMatrix, translationMatrix);

    return transformMatrix;
}

void DrawEntity(raylib::Model& model, Entity entity, bool drawBound) {
    TransformComponent& transform = transformStorage.Get<TransformComponent>(entity);
    raylib::Matrix transformMatrix = MatrixFromTransformComponent(transform); // You need to implement this

    model.transform = transformMatrix;
    model.Draw({});

    if (drawBound) {
        model.GetTransformedBoundingBox().Draw();
    }
}

int main() {
    // Create window
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;
    raylib::Window window(screenWidth, screenHeight, "CS381 - Assignment 8");

	raylib::BufferedInput inputs;
	inputs["SPACE"] = raylib::Action::key(KEY_SPACE).SetPressedCallback([]{
		kinematicsStorage.GetOrAllocate<Kinematics>(selectedEntity).speed = 0;
	}).move();
	inputs["TAB"] = raylib::Action::key(KEY_TAB).SetPressedCallback([]{
		selectedEntity = (selectedEntity + 1) % 10; // Cycle through entities
	}).move();
	inputs["W"] = raylib::Action::key(KEY_W).SetPressedCallback([]{
		kinematicsStorage.GetOrAllocate<Kinematics>(selectedEntity).shouldAccelerate = true;
		kinematicsStorage.GetOrAllocate<Kinematics>(selectedEntity).speed += 1;
	}).move();
	inputs["S"] = raylib::Action::key(KEY_S).SetPressedCallback([]{
		kinematicsStorage.GetOrAllocate<Kinematics>(selectedEntity).speed = std::max(0.0f, kinematicsStorage.GetOrAllocate<Kinematics>(selectedEntity).speed - 1);
	}).move();
	inputs["A"] = raylib::Action::key(KEY_A).SetPressedCallback([]{
		transformStorage.GetOrAllocate<TransformComponent>(selectedEntity).yaw -= 5;
	}).move();
	inputs["D"] = raylib::Action::key(KEY_D).SetPressedCallback([]{
		transformStorage.GetOrAllocate<TransformComponent>(selectedEntity).yaw += 5;
	}).move();
	inputs["Q"] = raylib::Action::key(KEY_Q).SetPressedCallback([]{
		TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(selectedEntity);
		raylib::Quaternion qPitch = QuaternionFromAxisAngle({1.0f, 0.0f, 0.0f}, 5 * DEG2RAD);  // Pitch up
		transform.rotation = QuaternionMultiply(transform.rotation, qPitch);
	}).move();

	inputs["E"] = raylib::Action::key(KEY_E).SetPressedCallback([]{
		TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(selectedEntity);
		raylib::Quaternion qPitch = QuaternionFromAxisAngle({1.0f, 0.0f, 0.0f}, -5 * DEG2RAD);  // Pitch down
		transform.rotation = QuaternionMultiply(transform.rotation, qPitch);
	}).move();

	inputs["R"] = raylib::Action::key(KEY_R).SetPressedCallback([]{
		TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(selectedEntity);
		raylib::Quaternion qRoll = QuaternionFromAxisAngle({0.0f, 0.0f, 1.0f}, 5 * DEG2RAD);  // Roll right
		transform.rotation = QuaternionMultiply(transform.rotation, qRoll);
	}).move();

	inputs["F"] = raylib::Action::key(KEY_F).SetPressedCallback([]{
		TransformComponent& transform = transformStorage.GetOrAllocate<TransformComponent>(selectedEntity);
		raylib::Quaternion qRoll = QuaternionFromAxisAngle({0.0f, 0.0f, 1.0f}, -5 * DEG2RAD);  // Roll left
		transform.rotation = QuaternionMultiply(transform.rotation, qRoll);
	}).move();

	raylib::Model plane = LoadModel("381Resources/meshes/PolyPlane.glb");
	raylib::Model shipModel0 = LoadModel("381Resources/meshes/Container_ShipLarge.glb");
	raylib::Model shipModel1 = LoadModel("381Resources/meshes/CargoG_HOSBrigadoon.glb");
	raylib::Model shipModel2 = LoadModel("381Resources/meshes/ddg51.glb");
	raylib::Model shipModel3 = LoadModel("381Resources/meshes/OilTanker.glb");
	raylib::Model shipModel4 = LoadModel("381Resources/meshes/SmitHouston_Tug.glb");

	shipModel0.transform = MatrixScale(0.5f, 0.5f, 0.5f);
	shipModel1.transform = MatrixScale(0.00000000000000005f, 0.000000000000005f, 0.00050000000000f);
	shipModel2.transform = MatrixScale(0.5f, 0.5f, 0.5f);
	shipModel3.transform = MatrixScale(0.5f, 0.5f, 0.5f);
	shipModel4.transform = MatrixScale(0.5f, 0.5f, 0.5f);

	InitializeComponents();
	InitializeScene();

    // Main loop
    bool keepRunning = true;
    while(!window.ShouldClose() && keepRunning) {
    
		float deltaTime = window.GetFrameTime();

		inputs.PollEvents();

		Update2DPhysics(transformStorage, kinematicsStorage, deltaTime); // For ships
		Update3DPhysics(transformStorage, kinematicsStorage, deltaTime); // For planes

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

				DrawEntity(shipModel4, ship0, selectedEntity == ship0);
				DrawEntity(shipModel4, ship1, selectedEntity == ship1);
				DrawEntity(shipModel4, ship2, selectedEntity == ship2);
				DrawEntity(shipModel4, ship3, selectedEntity == ship3);
				DrawEntity(shipModel4, ship4, selectedEntity == ship4);
				DrawEntity(plane, plane0, selectedEntity == plane0);
				DrawEntity(plane, plane1, selectedEntity == plane1);
				DrawEntity(plane, plane2, selectedEntity == plane2);
				DrawEntity(plane, plane3, selectedEntity == plane3);
				DrawEntity(plane, plane4, selectedEntity == plane4);
			}
			camera.EndMode();

			// Measure our FPS
			DrawFPS(10, 10);
		}
		window.EndDrawing();
    }
    return 0;
}