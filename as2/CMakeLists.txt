cmake_minimum_required(VERSION 3.18)
project(as2 LANGUAGES CXX)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as2 ${sources})
target_link_libraries(as2 PUBLIC raylib raylib_cpp)
set_property(TARGET as2 PROPERTY CXX_STANDARD 20)
