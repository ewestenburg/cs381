cmake_minimum_required(VERSION 3.18)
project(as6 LANGUAGES CXX)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as6 ${sources})
target_link_libraries(as6 PUBLIC raylib raylib_cpp)
set_property(TARGET as6 PROPERTY CXX_STANDARD 20)

configure_file(381Resources/meshes/OrientExplorer.glb 381Resources/meshes/OrientExplorer.glb COPYONLY)
configure_file(381Resources/meshes/PolyPlane.glb 381Resources/meshes/PolyPlane.glb COPYONLY)
configure_file(381Resources/meshes/CargoG_HOSBrigadoon.glb 381Resources/meshes/CargoG_HOSBrigadoon.glb COPYONLY)
configure_file(381Resources/meshes/ddg51.glb 381Resources/meshes/ddg51.glb COPYONLY)
configure_file(381Resources/meshes/OilTanker.glb 381Resources/meshes/OilTanker.glb COPYONLY)
configure_file(381Resources/meshes/SmitHouston_Tug.glb 381Resources/meshes/SmitHouston_Tug.glb COPYONLY)