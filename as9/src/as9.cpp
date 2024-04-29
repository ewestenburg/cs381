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
#include <random>
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
	Person,
    Obstacle1,
    Obstacle2,
    Obstacle3
};

// Global component storages
ComponentStorage transformStorage(sizeof(TransformComponent));
ComponentStorage kinematicsStorage(sizeof(Kinematics));
ComponentStorage renderStorage(sizeof(RenderComponent));
int selectedEntity = 0;
bool isJumping = false;
float jumpVelocity = 80.0f;  // Initial jump velocity
float gravity = 9.8f;  // Gravity pulling the player down after the jump
bool gameOver = false;
bool gamePaused = false;
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(300, 700);
int score = 0;

void InitializeComponents() {
	size_t numEntities = 5;  //for 5 ships and 5 planes
	transformStorage.Allocate<TransformComponent>(numEntities * 2);
	kinematicsStorage.Allocate<Kinematics>(numEntities * 2);
	renderStorage.Allocate<RenderComponent>(numEntities * 2);
}

void InitializeScene() {
    Entity person = static_cast<Entity>(Person);
    TransformComponent& personTransform = transformStorage.GetOrAllocate<TransformComponent>(Person);
    personTransform.position = raylib::Vector3{450.0f, 1.0f, 0.0f};
    personTransform.rotation = QuaternionFromEuler(0, -90.0f * DEG2RAD, 0); // Facing right

    Kinematics& personKinematics = kinematicsStorage.GetOrAllocate<Kinematics>(Person);
    personKinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
    personKinematics.speed = 0.0f; 
    personKinematics.maxSpeed = 200.0f; 
    personKinematics.acceleration = 100.0f; 

    Entity obstacle1 = static_cast<Entity>(Obstacle1);
    TransformComponent& obstacle1Transform = transformStorage.GetOrAllocate<TransformComponent>(Obstacle1);
    obstacle1Transform.position = raylib::Vector3{-50.0f, 0.0f, 0.0f};
    obstacle1Transform.rotation = QuaternionFromEuler(-115.0f, -90.0f * DEG2RAD, 0.25f); // Facing right

    Kinematics& obstacle1Kinematics = kinematicsStorage.GetOrAllocate<Kinematics>(Obstacle1);
    obstacle1Kinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
    obstacle1Kinematics.speed = 0.0f; 
    obstacle1Kinematics.maxSpeed = 0.0f; 
    obstacle1Kinematics.acceleration = 0.0f; 

    Entity obstacle2 = static_cast<Entity>(Obstacle2);
    TransformComponent& obstacle2Transform = transformStorage.GetOrAllocate<TransformComponent>(Obstacle2);
    obstacle2Transform.position = raylib::Vector3{-500.0f, 0.0f, 0.0f};
    obstacle2Transform.rotation = QuaternionFromEuler(-115.0f, -90.0f * DEG2RAD, 0.25f); // Facing right

    Kinematics& obstacle2Kinematics = kinematicsStorage.GetOrAllocate<Kinematics>(Obstacle2);
    obstacle2Kinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
    obstacle2Kinematics.speed = 0.0f; 
    obstacle2Kinematics.maxSpeed = 0.0f; 
    obstacle2Kinematics.acceleration = 0.0f; 

    Entity obstacle3 = static_cast<Entity>(Obstacle3);
    TransformComponent& obstacle3Transform = transformStorage.GetOrAllocate<TransformComponent>(Obstacle3);
    obstacle3Transform.position = raylib::Vector3{-1000.0f, 0.0f, 0.0f};
    obstacle3Transform.rotation = QuaternionFromEuler(-115.0f, -90.0f * DEG2RAD, 0.25f); // Facing right

    Kinematics& obstacle3Kinematics = kinematicsStorage.GetOrAllocate<Kinematics>(Obstacle3);
    obstacle3Kinematics.velocity = raylib::Vector3{0.0f, 0.0f, 0.0f};
    obstacle3Kinematics.speed = 0.0f; 
    obstacle3Kinematics.maxSpeed = 0.0f; 
    obstacle3Kinematics.acceleration = 0.0f; 
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

void UpdatePhysics(ComponentStorage& transformStorage, ComponentStorage& kinematicsStorage, float deltaTime) {
    TransformComponent& transform = transformStorage.Get<TransformComponent>(Person);
    Kinematics& kinematics = kinematicsStorage.Get<Kinematics>(Person);

    // Gravity application
    if (transform.position.y > 0 || isJumping) {
        kinematics.velocity.y -= gravity * deltaTime; // Apply gravity
    }

    // Update position
    transform.position.x += kinematics.velocity.x * deltaTime;
    transform.position.y += kinematics.velocity.y * deltaTime;

    // Check if landed on the ground
    if (transform.position.y < 0) {
        transform.position.y = 0; // Clamp to ground level
        kinematics.velocity.y = 0; // Stop vertical movement
        isJumping = false; // Reset jumping state
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
    raylib::Matrix transformMatrix = MatrixFromTransformComponent(transform); 

    model.transform = transformMatrix;
    model.Draw({});

    if (drawBound) {
        model.GetTransformedBoundingBox().Draw();
    }
}

BoundingBox GetTransformedBoundingBox(raylib::Model& model, const TransformComponent& transform) {
    raylib::Matrix transformMatrix = MatrixFromTransformComponent(transform);
    model.transform = transformMatrix;
    return model.GetTransformedBoundingBox();
}

bool CheckCollisions(raylib::Model& personModel, raylib::Model& obstacleModel) {
    TransformComponent& personTransform = transformStorage.Get<TransformComponent>(Person);
    BoundingBox personBBox = GetTransformedBoundingBox(personModel, personTransform);

    for (Entity e = Obstacle1; e <= Obstacle2; e++) {
        TransformComponent& obstacleTransform = transformStorage.Get<TransformComponent>(e);
        BoundingBox obstacleBBox = GetTransformedBoundingBox(obstacleModel, obstacleTransform);
        if (CheckCollisionBoxes(personBBox, obstacleBBox)) {
            return true;  // Collision detected
        }
    }
    return false;
}

Entity GetClosestObstacleAhead(float playerX) {
    Entity closest = Obstacle1;
    float minDistance = std::numeric_limits<float>::max();

    std::vector<Entity> obstacles = {Obstacle1, Obstacle2, Obstacle3};
    for (Entity obs : obstacles) {
        float distance = transformStorage.Get<TransformComponent>(obs).position.x - playerX;
        if (distance > 0 && distance < minDistance) { // Obstacle ahead and closest
            closest = obs;
            minDistance = distance;
        }
    }

    return closest;
}

void UpdateObstacles(raylib::Vector3& playerPosition) {
    Entity firstObstacle = Obstacle1, secondObstacle = Obstacle2, thirdObstacle = Obstacle3;

    // Calculate which obstacle is the leftmost
    float leftMostX = std::min({
        transformStorage.Get<TransformComponent>(firstObstacle).position.x,
        transformStorage.Get<TransformComponent>(secondObstacle).position.x,
        transformStorage.Get<TransformComponent>(thirdObstacle).position.x
    });

    // Check and recycle each obstacle if it's off-screen to the right
    std::vector<Entity> obstacles = {firstObstacle, secondObstacle, thirdObstacle};
    for (Entity obstacle : obstacles) {
        if (transformStorage.Get<TransformComponent>(obstacle).position.x > playerPosition.x + 500) {
            int randomSpacing = distribution(generator);  // Get a random spacing value between 300 and 700
            // Move this obstacle to the left of the leftmost obstacle with random spacing
            transformStorage.Get<TransformComponent>(obstacle).position.x = leftMostX - randomSpacing;
            std::cout << "Recycled Obstacle " << static_cast<int>(obstacle) 
                      << " to " << leftMostX - randomSpacing << std::endl;
        }
    }
}

void UpdateScoreAndObstacles(raylib::Vector3& playerPosition) {
    static Entity lastObstacleJumped = 1; // Track the last obstacle jumped over
    Entity currentClosestObstacle = GetClosestObstacleAhead(playerPosition.x);

    if (score == 0 && currentClosestObstacle == lastObstacleJumped && playerPosition.y > transformStorage.Get<TransformComponent>(currentClosestObstacle).position.y + 50) {
        score++;
    }

    if (currentClosestObstacle != lastObstacleJumped && playerPosition.y > transformStorage.Get<TransformComponent>(currentClosestObstacle).position.y + 50) {
        score++;
        lastObstacleJumped = currentClosestObstacle; // Update the last jumped obstacle
        std::cout << "Scored! Total score: " << score << std::endl;
    }

    UpdateObstacles(playerPosition); // Continue to manage obstacles
}

int main() {
    // Create window
    const int screenWidth = 800 * 2;
    const int screenHeight = 450 * 2;
    raylib::Window window(screenWidth, screenHeight, "CS381 - Assignment 9");

    // Adjusting inputs for jump and movement
    raylib::BufferedInput inputs;
	inputs["MOVE_RIGHT"] = raylib::Action::key(KEY_W).SetPressedCallback([&]{
    if (!isJumping) {  // Optionally check if not jumping to move
        kinematicsStorage.Get<Kinematics>(Person).velocity.x = -25.0f; // Positive x-direction velocity
    }
    }).move();
    inputs["JUMP"] = raylib::Action::key(KEY_S).SetPressedCallback([&]{
        if (!isJumping) { // Ensure we are on the ground
            isJumping = true;
            kinematicsStorage.Get<Kinematics>(Person).velocity.y = jumpVelocity; // Initial jump velocity
        }
    }).move();

    raylib::Model person = LoadModel("models/rp_mei_posed_001_30k.obj");
    raylib::Model obstacle = LoadModel("models/16314_MTBike_obstacle05_v1.obj");
    obstacle.transform = MatrixScale(5.0f, 5.0f, 5.0f);

    InitializeComponents();
    InitializeScene();

    // Main loop
    bool keepRunning = true;
    bool gameOver = false;  // Game over state

    TransformComponent& personTransform = transformStorage.GetOrAllocate<TransformComponent>(Person);

    while(!window.ShouldClose() && keepRunning) {
        float deltaTime = window.GetFrameTime();
        if(!gamePaused){
            inputs.PollEvents();

            // Update physics considering jump and collisions
            UpdatePhysics(transformStorage, kinematicsStorage, deltaTime);
            UpdateScoreAndObstacles(personTransform.position);
            if (isJumping) {
                Kinematics& kin = kinematicsStorage.Get<Kinematics>(Person);
                kin.velocity.y -= gravity * deltaTime;  // Apply gravity to the jump velocity
                if (kin.velocity.y <= 0 && transformStorage.Get<TransformComponent>(Person).position.y <= 0) {
                    isJumping = false;  // Stop jumping when reaching the ground level
                    kin.velocity.y = 0;
                    transformStorage.Get<TransformComponent>(Person).position.y = 0;  // Reset to ground level
                }
            }

            // Collision detection
            if (!gameOver) {  // Check collisions only if the game is not over
                gameOver = CheckCollisions(person, obstacle);
            }

            if (gameOver) {
                gamePaused = true;  // Pause the game
            }
        }

        personTransform = transformStorage.GetOrAllocate<TransformComponent>(Person);

        // Rendering
        window.BeginDrawing();
        {
            window.ClearBackground(BLACK);  // Clear screen

            auto camera = raylib::Camera(
                raylib::Vector3(personTransform.position.x - 250, 120, -500), // Camera is behind and above the player
                raylib::Vector3(personTransform.position.x, 0, 300), // Camera looks towards the player
                raylib::Vector3::Up(),
                45.0f,
                CAMERA_PERSPECTIVE
            );
            camera.BeginMode();

            // Skybox and ground
            cs381::SkyBox skybox("381Resources/textures/skybox.png");
            skybox.Draw();

            auto mesh = raylib::Mesh::Plane(10000, 10000, 50, 50, 25);
            raylib::Model ground = ((raylib::Mesh*)&mesh)->LoadModelFrom();
            raylib::Texture grass("381Resources/textures/grass.jpg");
            grass.SetFilter(TEXTURE_FILTER_BILINEAR);
            grass.SetWrap(TEXTURE_WRAP_REPEAT);
            ground.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grass;
            ground.Draw({});

            // Draw entities
            DrawEntity(person, Person, true);
            DrawEntity(obstacle, Obstacle1, false);
            DrawEntity(obstacle, Obstacle2, false);
            DrawEntity(obstacle, Obstacle3, false);

            camera.EndMode();

            DrawText("Hold W to increase velocity", screenWidth - 325, 750, 20, BLACK);
            DrawText("Hold S to Jump", screenWidth - 250, 700, 20, BLACK);

            // Score display on the left corner
            DrawText(TextFormat("Score: %d", score), 10, 750, 20, BLACK);

            if (gamePaused) {
                DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 20) / 2, screenHeight / 2 - 20, 20, RED);
                DrawText("Press SPACE to restart", screenWidth / 2 - MeasureText("Press SPACE to restart", 20) / 2, screenHeight / 2 + 20, 20, RED);
            }

            // Display FPS
            DrawFPS(10, 10);
        }
        window.EndDrawing();

        // Check for restart
        if (gamePaused && IsKeyPressed(KEY_SPACE)) {
            InitializeScene(); // Reset the scene
            gameOver = false;
            gamePaused = false;
        }
    }
    return 0;
}