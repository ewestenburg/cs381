#include "raylib-cpp.hpp"

#define GUI_VOLUMECONTROL_IMPLEMENTATION
#include "VolumeControl.h"

GuiVolumeControlState volumeControlState;
raylib::AudioDevice audio;    

Sound soundEffect;
Sound dialogueTrack;
Music backgroundMusic;

bool buttonPressed = false;

void LoadAudioFiles() {
    soundEffect = LoadSound("381Resources/audio/ping.wav");
    dialogueTrack = LoadSound("381Resources/audio/crowd.wav");
    backgroundMusic = LoadMusicStream("381Resources/audio/price-of-freedom.mp3");
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

    if (GuiButton((Rectangle){24, 304, 256, 24}, "Ping") && !buttonPressed) {
        buttonPressed = true;
        PlaySound(soundEffect);
    } else {
        buttonPressed = false;
    }

    // Check if the space bar is pressed
    if (IsKeyPressed(KEY_SPACE)) {
        PlaySound(soundEffect);
    }
}

int main() {
    InitWindow(800, 600, "CS381 - Assignment 5");
    SetTargetFPS(60);

    volumeControlState = InitGuiVolumeControl();

    LoadAudioFiles();

    while (!WindowShouldClose()) {
        UpdateAudio();

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
