#include "raylib-cpp.hpp"

#define GUI_VOLUMECONTROL_IMPLEMENTATION
#include "VolumeControl.h"

GuiVolumeControlState volumeControlState;
raylib::AudioDevice audio;

Sound soundEffect;
Sound dialogueTrack;
Sound damnEffect;
Music backgroundMusic;

bool buttonPressed = false;
bool guiLightTheme = true;
int currentSlider = 0; 

void LoadAudioFiles() {
    soundEffect = LoadSound("381Resources/audio/ping.wav");
    dialogueTrack = LoadSound("381Resources/audio/crowd.wav");
    backgroundMusic = LoadMusicStream("381Resources/audio/price-of-freedom.mp3");
    damnEffect = LoadSound("381Resources/audio/damn.wav");
    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, volumeControlState.MusicSliderValue / 100.0f);
    PlaySound(dialogueTrack);
    SetSoundVolume(dialogueTrack, volumeControlState.MusicSliderValue / 100.0f);
}

void UpdateAudio() {
    UpdateMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, volumeControlState.MusicSliderValue / 100.0f);
    SetSoundVolume(soundEffect, volumeControlState.SFXSliderValue / 100.0f);
    SetSoundVolume(dialogueTrack, volumeControlState.DialogueSliderValue / 100.0f);

    if (currentSlider == 0) {
        if (IsKeyPressed(KEY_DOWN)) {
            volumeControlState.SFXSliderValue -= 5;
            volumeControlState.SFXSliderValue = std::max(static_cast<float>(volumeControlState.SFXSliderValue), 0.0f);
        }
        if (IsKeyPressed(KEY_UP)) {
            volumeControlState.SFXSliderValue += 5;
            volumeControlState.SFXSliderValue = std::min(static_cast<float>(volumeControlState.SFXSliderValue), 100.0f);
        }
    }

    else if(currentSlider == 1){
        if (IsKeyPressed(KEY_DOWN)) {
            volumeControlState.MusicSliderValue -= 5;
            volumeControlState.MusicSliderValue = std::max(static_cast<float>(volumeControlState.MusicSliderValue), 0.0f);
        }
        if (IsKeyPressed(KEY_UP)) {
            volumeControlState.MusicSliderValue += 5;
            volumeControlState.MusicSliderValue = std::min(static_cast<float>(volumeControlState.MusicSliderValue), 100.0f);
        }
    }

    else if(currentSlider == 2){
        if (IsKeyPressed(KEY_DOWN)) {
            volumeControlState.DialogueSliderValue -= 5;
            volumeControlState.DialogueSliderValue = std::max(static_cast<float>(volumeControlState.DialogueSliderValue), 0.0f);
        }
        if (IsKeyPressed(KEY_UP)) {
            volumeControlState.DialogueSliderValue += 5;
            volumeControlState.DialogueSliderValue = std::min(static_cast<float>(volumeControlState.DialogueSliderValue), 100.0f);
        }
    }

    // Check if the tab key is pressed to switch between sliders
    if (IsKeyPressed(KEY_TAB)) {
        currentSlider = (currentSlider + 1) % 3; // There are three sliders
    }

    if (GuiButton((Rectangle){24, 304, 256, 24}, "Ping") && !buttonPressed) {
        buttonPressed = true;
        PlaySound(soundEffect);
    } else {
        buttonPressed = false;
    }

    if (GuiButton((Rectangle){24, 354, 306, 24}, "Try this") && !buttonPressed) {
        buttonPressed = true;
        PlaySound(damnEffect);
    } else {
        buttonPressed = false;
    }

    // Check if the space bar is pressed
    if (IsKeyPressed(KEY_SPACE)) {
        PlaySound(soundEffect);
    }
}

void UpdateGUI(){

    if (GuiButton((Rectangle){24, 404, 356, 24}, "Change Theme") && !buttonPressed) {
        buttonPressed = true;
        guiLightTheme = !guiLightTheme;
    } else {
        buttonPressed = false;
    }

    if(guiLightTheme){
        GuiLoadStyleDefault();
    }
    else{
        //GUI dark theme
        GuiLoadStyleDefault();
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, raylib::DARKGRAY);
        GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, raylib::RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, raylib::RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_COLOR_DISABLED, raylib::GRAY);
        GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, raylib::DARKGRAY);
        GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, raylib::GRAY);
        GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, raylib::GRAY);
        GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, raylib::DARKGRAY);
        GuiSetStyle(DEFAULT, BORDER_WIDTH, 1);
    }
}

int main() {
    InitWindow(800, 600, "CS381 - Assignment 5");
    SetTargetFPS(60);

    volumeControlState = InitGuiVolumeControl();

    LoadAudioFiles();

    while (!WindowShouldClose()) {
        UpdateAudio();
        UpdateGUI();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        GuiVolumeControl(&volumeControlState);

        EndDrawing();
    }

    // cleanup
    UnloadSound(soundEffect);
    UnloadSound(dialogueTrack);
    UnloadMusicStream(backgroundMusic);
    CloseWindow();

    return 0;
}