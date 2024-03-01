cmake_minimum_required(VERSION 3.18)
project(as3 LANGUAGES CXX)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as3 ${sources})
target_link_libraries(as3 PUBLIC raylib raylib_cpp)
set_property(TARGET as3 PROPERTY CXX_STANDARD 20)
