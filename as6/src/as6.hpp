#pragma once

#include <vector>
#include <string>
#include <memory>
#include "raylib-cpp.hpp"

class TransformComponent {
public:
    raylib::Vector3 position;
    float heading;
};

class RenderComponent {
public:
    raylib::Model model;
    bool drawBoundingBox;
};

class PhysicsComponent {
public:
    raylib::Vector3 velocity;
    float maxSpeed;
    float acceleration;
    float turningRate;
};

class InputComponent {
public:
    void UpdateInput(TransformComponent& transform, PhysicsComponent& physics);
};

class Entity {
public:
    TransformComponent transform;
    RenderComponent render;
    PhysicsComponent physics;
    InputComponent input;
    bool isSelected;

    void Update(float deltaTime);
    void Draw();
};

class SelectionManager {
public:
    SelectionManager(std::vector<std::unique_ptr<Entity>>& entities);

    void Update();
    void DrawBoundingBoxes();

private:
    std::vector<std::unique_ptr<Entity>>& entities;
    size_t selectedIndex;
};

class Scene {
public:
    Scene();
    ~Scene();

    void Init();
    void Update(float deltaTime);
    void Draw();

private:
    raylib::Camera3D camera;
    std::vector<std::unique_ptr<Entity>> entities;
    SelectionManager selectionManager;
};