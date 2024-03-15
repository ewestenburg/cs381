cmake_minimum_required(VERSION 3.18)
project(as5 LANGUAGES CXX)

add_subdirectory(raylib-cpp)

file(GLOB sources "src/*.cpp" "src/*.c")
add_executable(as5 ${sources})
target_link_libraries(as5 PUBLIC raylib raygui raylib_cpp)
set_property(TARGET as5 PROPERTY CXX_STANDARD 20)

configure_file(381Resources/audio/ping.wav 381Resources/audio/ping.wav COPYONLY)
configure_file(381Resources/audio/crowd.wav 381Resources/audio/crowd.wav COPYONLY)
configure_file(381Resources/audio/price-of-freedom.mp3 381Resources/audio/price-of-freedom.mp3 COPYONLY)
configure_file(381Resources/audio/damn.wav 381Resources/audio/damn.wav COPYONLY)