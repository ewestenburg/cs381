cmake_minimum_required(VERSION 3.18)
project(as8 LANGUAGES CXX)
add_subdirectory(raylib-cpp)
file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as8 ${sources})
target_link_libraries(as8 PUBLIC raylib raylib_cpp raylib::buffered)
set_property(TARGET as8 PROPERTY CXX_STANDARD 20)

configure_file(381Resources/meshes/OrientExplorer.glb 381Resources/meshes/OrientExplorer.glb COPYONLY)
configure_file(381Resources/meshes/PolyPlane.glb 381Resources/meshes/PolyPlane.glb COPYONLY)
configure_file(381Resources/meshes/CargoG_HOSBrigadoon.glb 381Resources/meshes/CargoG_HOSBrigadoon.glb COPYONLY)
configure_file(381Resources/meshes/ddg51.glb 381Resources/meshes/ddg51.glb COPYONLY)
configure_file(381Resources/meshes/OilTanker.glb 381Resources/meshes/OilTanker.glb COPYONLY)
configure_file(381Resources/meshes/SmitHouston_Tug.glb 381Resources/meshes/SmitHouston_Tug.glb COPYONLY)
configure_file(381Resources/meshes/Container_ShipLarge.glb 381Resources/meshes/Container_ShipLarge.glb COPYONLY)
configure_file(381Resources/textures/skybox.png 381Resources/textures/skybox.png COPYONLY)
configure_file(381Resources/textures/grass.jpg 381Resources/textures/grass.jpg COPYONLY)
configure_file(381Resources/textures/water.jpg 381Resources/textures/water.jpg COPYONLY)

include(includeable.cmake)

make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl330/skybox.vs generated/glsl330/skybox.vs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl330/skybox.fs generated/glsl330/skybox.fs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl330/cubemap.fs generated/glsl330/cubemap.fs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl330/cubemap.vs generated/glsl330/cubemap.vs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl100/skybox.vs generated/glsl100/skybox.vs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl100/skybox.fs generated/glsl100/skybox.fs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl100/cubemap.vs generated/glsl100/cubemap.vs)
make_includeable(raylib-cpp/raylib/examples/models/resources/shaders/glsl100/cubemap.fs generated/glsl100/cubemap.fs)
