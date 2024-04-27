#include "as6.hpp"

void InputComponent::UpdateInput(TransformComponent& transform, PhysicsComponent& physics) {
    if (IsKeyPressed(KEY_W))
        physics.velocity.z += physics.acceleration;
    if (IsKeyPressed(KEY_S))
        physics.velocity.z -= physics.acceleration;
    if (IsKeyPressed(KEY_A))
        transform.heading += physics.turningRate;
    if (IsKeyPressed(KEY_D))
        transform.heading -= physics.turningRate;
    if (IsKeyPressed(KEY_SPACE))
        physics.velocity = raylib::Vector3{ 0.0f, 0.0f, 0.0f };
}

void Entity::Update(float deltaTime) {
    if (isSelected)
        input.UpdateInput(transform, physics);

    // Update position based on velocity
    transform.position = Vector3Add(transform.position, Vector3Scale(physics.velocity, deltaTime));

    // Update orientation based on heading
    render.model.transform = raylib::Transform(render.model.transform).RotateY(transform.heading);
}

void Entity::Draw() {
    DrawModel(render.model, transform.position, 1.0f, RED);
}

SelectionManager::SelectionManager(std::vector<std::unique_ptr<Entity>>& entities) : entities(entities), selectedIndex(0) {}

void SelectionManager::Update() {
    if (IsKeyPressed(KEY_TAB)) {
        entities[selectedIndex]->isSelected = false;
        selectedIndex = (selectedIndex + 1) % entities.size();
        entities[selectedIndex]->isSelected = true;
    }
}

void SelectionManager::DrawBoundingBoxes() {
    for (size_t i = 0; i < entities.size(); ++i) {
        if (entities[i]->isSelected) {
            BoundingBox box = entities[i]->render.model.GetBoundingBox();
            box.min = Vector3Transform(box.min, entities[i]->render.model.transform);
            box.max = Vector3Transform(box.max, entities[i]->render.model.transform);
            DrawBoundingBox(box, BLACK);
        }
    }
}

Scene::Scene() : selectionManager(entities) {}

Scene::~Scene() {
    CloseWindow();
}

void Scene::Init() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "CS381 - Assignment 6");

    camera.position = raylib::Vector3(0, 200, 0);  
    camera.target = raylib::Vector3(0, 0, 0);      
    camera.up = (raylib::Vector3){ 0.0f, 0.0f, -1.0f }; 
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    SetTargetFPS(60);
    
    std::unique_ptr<Entity> ship1 = std::make_unique<Entity>();
    
    // Ship properties
    
    ship1->transform.position = raylib::Vector3{ 0, 0, 0 };
    ship1->render.model = LoadModel("381Resources/meshes/OrientExplorer.glb");
    ship1->physics.maxSpeed = 10.0f;
    ship1->physics.acceleration = 2.0f;
    ship1->physics.turningRate = 1.0f;

    ship1->render.model.transform = raylib::Transform(ship1->render.model.transform).Scale(0.005, 0.005, 0.005);

    entities.push_back(std::move(ship1));

    std::unique_ptr<Entity> ship2 = std::make_unique<Entity>();
    ship2->transform.position = raylib::Vector3{ -50, 0, 0 };
    ship2->render.model = LoadModel("381Resources/meshes/CargoG_HOSBrigadoon.glb");
    ship2->physics.maxSpeed = 25.0f;
    ship2->physics.acceleration = 0.5f;
    ship2->physics.turningRate = 0.2f;

    ship2->render.model.transform = raylib::Transform(ship2->render.model.transform).Scale(0.005, 0.005, 0.005);

    entities.push_back(std::move(ship2));
    
    std::unique_ptr<Entity> ship3 = std::make_unique<Entity>();
    ship3->transform.position = raylib::Vector3{ -25, 0, 0 };
    ship3->render.model = LoadModel("381Resources/meshes/ddg51.glb");
    ship3->physics.maxSpeed = 15.0f;
    ship3->physics.acceleration = 5.0f;
    ship3->physics.turningRate = 2.0f;

    ship3->render.model.transform = raylib::Transform(ship3->render.model.transform).Scale(0.5, 0.5, 0.5);

    entities.push_back(std::move(ship3));

    std::unique_ptr<Entity> ship4 = std::make_unique<Entity>();
    ship4->transform.position = raylib::Vector3{ 25, 0, 0 };
    ship4->render.model = LoadModel("381Resources/meshes/OilTanker.glb");
    ship4->physics.maxSpeed = 100.0f;
    ship4->physics.acceleration = 10.0f;
    ship4->physics.turningRate = 3.0f;

    ship4->render.model.transform = raylib::Transform(ship4->render.model.transform).Scale(0.001, 0.001, 0.001);

    entities.push_back(std::move(ship4));

    std::unique_ptr<Entity> ship5 = std::make_unique<Entity>();
    ship5->transform.position = raylib::Vector3{ 50, 0, 0 };
    ship5->render.model = LoadModel("381Resources/meshes/SmitHouston_Tug.glb");
    ship5->physics.maxSpeed = 5.0f;
    ship5->physics.acceleration = 3.0f;
    ship5->physics.turningRate = 1.0f;

    ship5->render.model.transform = raylib::Transform(ship5->render.model.transform).Scale(0.5, 0.5, 0.5);

    entities.push_back(std::move(ship5));

    //Planes

    std::unique_ptr<Entity> plane1 = std::make_unique<Entity>();
    plane1->transform.position = raylib::Vector3{ 0, -50, -50 };
    plane1->render.model = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane1->physics.maxSpeed = 5.0f;
    plane1->physics.acceleration = 3.0f;
    plane1->physics.turningRate = 1.0f;

    plane1->render.model.transform = raylib::Transform(plane1->render.model.transform).Scale(0.5, 0.5, 0.5);

    entities.push_back(std::move(plane1));

    std::unique_ptr<Entity> plane2 = std::make_unique<Entity>();
    plane2->transform.position = raylib::Vector3{ -50, -50, -50 };
    plane2->render.model = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane2->physics.maxSpeed = 5.0f;
    plane2->physics.acceleration = 3.0f;
    plane2->physics.turningRate = 1.0f;
    plane2->render.model.transform = raylib::Transform(plane2->render.model.transform).Scale(0.5, 0.5, 0.5);
    entities.push_back(std::move(plane2));

    std::unique_ptr<Entity> plane3 = std::make_unique<Entity>();
    plane3->transform.position = raylib::Vector3{ -25, -50, -50 };
    plane3->render.model = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane3->physics.maxSpeed = 5.0f;
    plane3->physics.acceleration = 3.0f;
    plane3->physics.turningRate = 1.0f;
    plane3->render.model.transform = raylib::Transform(plane3->render.model.transform).Scale(0.5, 0.5, 0.5);
    entities.push_back(std::move(plane3));

    std::unique_ptr<Entity> plane4 = std::make_unique<Entity>();
    plane4->transform.position = raylib::Vector3{ 25, -50, -50 };
    plane4->render.model = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane4->physics.maxSpeed = 5.0f;
    plane4->physics.acceleration = 3.0f;
    plane4->physics.turningRate = 1.0f;
    plane4->render.model.transform = raylib::Transform(plane4->render.model.transform).Scale(0.5, 0.5, 0.5);
    entities.push_back(std::move(plane4));

    std::unique_ptr<Entity> plane5 = std::make_unique<Entity>();
    plane5->transform.position = raylib::Vector3{ 50, -50, -50 };
    plane5->render.model = LoadModel("381Resources/meshes/PolyPlane.glb");
    plane5->physics.maxSpeed = 5.0f;
    plane5->physics.acceleration = 3.0f;
    plane5->physics.turningRate = 1.0f;
    plane5->render.model.transform = raylib::Transform(plane5->render.model.transform).Scale(0.5, 0.5, 0.5);
    entities.push_back(std::move(plane5));
}

void Scene::Update(float deltaTime) {
    // Update selection and entities
    selectionManager.Update();
    for (auto& entity : entities)
        entity->Update(deltaTime);
}

void Scene::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);

    for (auto& entity : entities) {
        entity->Draw();
        if (entity->isSelected) {
            BoundingBox box = entity->render.model.GetBoundingBox();
            box.min = Vector3Transform(box.min, entity->render.model.transform);
            box.max = Vector3Transform(box.max, entity->render.model.transform);
            DrawBoundingBox(box, BLACK);
        }
    }

    EndMode3D();

    EndDrawing();
}

int main() {
    Scene scene;
    scene.Init();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        scene.Update(deltaTime);
        scene.Draw();
    }

    return 0;
}
int main() {
    Scene scene;
    scene.Init();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        scene.Update(deltaTime);
        scene.Draw();
    }

    return 0;
}