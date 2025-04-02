#pragma once

#include <vector>
#include "Scene.h"

#include "imgui.h"

struct SDL_Window;

// Main application class of the program.
class Application {
public:
    Application(const std::vector<Scene*>& scenes);
    ~Application();

    // Run the application.
    int Run();

private:
    // The main loop of the application.
    void MainLoop(const ImGuiIO& io);
    // Draws the menu bar.
    void DrawMenuBar();
    // Draws the stats window.
    void DrawStatsWindow(const ImGuiIO& io);
    // Draws the settings window.
    void DrawSettingsWindow();
    // Draws the control window.
    void DrawControlWindow();
    // Draws modal to enter information about the new scene.
    void DrawNewSceneModal();
    // Creates the files for a new scene.
    bool CreateNewScene(const char* filename, const char* displayText);

    // All available scenes.
    std::vector<Scene*> scenes;
    // The currently shown scene.
    Scene* currentScene;
    // Show the Dear ImGui demo window.
    bool isDemoWindowVisible = false;
    // Show the stats window.
    bool isStatsWindowVisible = false;
    // Show the settings window.
    bool isSettingsWindowVisible = false;
    // Is the application still running?
    bool isRunning = true;
    // Performance counter value of the previous frame. Used to calculate the
    // delta time.
    uint64_t lastPerformanceCount = 0;

    SDL_Window* window = nullptr;
    bool isDockingInitialized = false;
    bool isPaused = false;
    bool isStepping = false;
    ImVec4 clearColor;

    bool isVsyncEnabled = true;
    bool isFramerateCapped = false;
    float framerateCap = 60;

    // New scene dialog.
    bool openNewSceneModal = false;
};