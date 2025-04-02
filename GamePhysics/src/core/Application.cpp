#include "Application.h"

#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <memory>
#include <stdio.h>

#include "ImGuizmo.h"
#include "Preferences.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "core/Draw.h"
#include "imgui.h"
#include "imgui_internal.h"

Application::Application(const std::vector<Scene*>& scenes)
    : scenes(scenes), clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)) {
    currentScene = *scenes.rbegin();
}

Application::~Application() {
    scenes.clear();
}

int Application::Run() {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
        0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    if (currentScene == nullptr) {
        printf("Error: No scene supplied.");
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                          SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("Game Physics", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Regular.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Regular.ttf", 32.0f);

    // Load preferences from file.
    Preferences::Load();
    isStatsWindowVisible = Preferences::GetBool("stats_window");
    isSettingsWindowVisible = Preferences::GetBool("settings_window");
    isDemoWindowVisible = Preferences::GetBool("demo_window");
    isVsyncEnabled = Preferences::GetBool("vsync");
    isFramerateCapped = Preferences::GetBool("framerate_capped", true);
    framerateCap = Preferences::GetFloat("framerate_cap", 60.0f);

    SDL_GL_SetSwapInterval(isVsyncEnabled); // Enable vsync

    // Initialize first scene.
    currentScene->OnEnable();

    MainLoop(io);

    Preferences::Save();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void Application::MainLoop(const ImGuiIO& io) {
    lastPerformanceCount = SDL_GetPerformanceCounter();
    float totalTime = 0;

    while (isRunning) {
        Uint64 frameStart = SDL_GetPerformanceCounter();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                isRunning = false;
            if (event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window))
                isRunning = false;
        }

        // Calculate delta time.
        Uint64 performanceCount = SDL_GetPerformanceCounter();
        float deltaTime = (float)(performanceCount - lastPerformanceCount) /
                          SDL_GetPerformanceFrequency();
        lastPerformanceCount = performanceCount;

        // Start the Dear ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        // Setup docking.
        ImGuiID dockspaceId = ImGui::GetID("CenterDockspace");
        

        if (!isDockingInitialized) {
            isDockingInitialized = true;

            // Only set up the docked layout if there was none saved yet.
            if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) {
                ImGui::DockBuilderRemoveNode(dockspaceId);
                ImGui::DockBuilderAddNode(dockspaceId,
                                          ImGuiDockNodeFlags_DockSpace);
                // Main node should cover entire window.
                ImGui::DockBuilderSetNodeSize(dockspaceId,
                                              ImGui::GetWindowSize());
                ImGuiID centerDockId = dockspaceId;
                // Create side dock spaces.
                ImGuiID leftDockId = ImGui::DockBuilderSplitNode(
                    centerDockId, ImGuiDir_Left, 1.0f, nullptr, &centerDockId);
                ImGuiID upDockId = ImGui::DockBuilderSplitNode(
                    centerDockId, ImGuiDir_Up, 0.10f, nullptr, &centerDockId);
                ImGuiID downDockId = ImGui::DockBuilderSplitNode(
                    centerDockId, ImGuiDir_Down, 0.25f, nullptr, &centerDockId);

                // Assign windows to dock spaces.
                ImGui::DockBuilderDockWindow("Viewport", centerDockId);
                ImGui::DockBuilderDockWindow("Inspector", leftDockId);
                ImGui::DockBuilderDockWindow("Control", upDockId);
                ImGui::DockBuilderDockWindow("Camera", downDockId);
                ImGui::DockBuilderFinish(dockspaceId);
            }
        }

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        // Submit a window filling the entire viewport.
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGuiWindowFlags hostWindowFlags = 0;
        hostWindowFlags |= ImGuiWindowFlags_NoTitleBar |
                           ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoDocking;
        hostWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                           ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockspaceWindow", nullptr, hostWindowFlags);
        ImGui::PopStyleVar(3);
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), 0);
        ImGui::End();

        DrawMenuBar();

        // Windows
        if (isDemoWindowVisible) {
            ImGui::ShowDemoWindow(&isDemoWindowVisible);
        }
        DrawStatsWindow(io);
        DrawControlWindow();
        DrawSettingsWindow();
        DrawNewSceneModal();

        // Show the current scene.
        if (!isPaused || isStepping) {
            totalTime += deltaTime;
            currentScene->Update(deltaTime);
        }

        currentScene->Render();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w,
                     clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        isStepping = false;

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);

        if (isFramerateCapped) {
            float elapsedMs =
                (float)(SDL_GetPerformanceCounter() - frameStart) /
                SDL_GetPerformanceFrequency() * 1000.0f;
            int sleep =
                std::max(0.0f, floor(1000.0f / framerateCap - elapsedMs));
            SDL_Delay(sleep);
        }
    }
}

void Application::DrawMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit", "Cmd+Q")) {
                isRunning = false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scenes")) {
            for (const auto& scene : scenes) {
                if (ImGui::MenuItem(scene->GetName(), nullptr,
                                    currentScene == scene)) {
                    std::cout << "Switch to scene " << scene->GetName() << "."
                              << std::endl;
                    // Switch scene
                    if (currentScene) {
                        currentScene->OnDisable();
                    }
                    currentScene = scene;
                    if (currentScene) {
                        currentScene->OnEnable();
                    }
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::MenuItem("Stats", nullptr, isStatsWindowVisible)) {
                isStatsWindowVisible = !isStatsWindowVisible;
                Preferences::SetBool("stats_window", isStatsWindowVisible);
                Preferences::Save();
            }
            if (ImGui::MenuItem("Dear ImGui Demo", nullptr, isDemoWindowVisible)) {
                isDemoWindowVisible = !isDemoWindowVisible;
                Preferences::SetBool("demo_window", isDemoWindowVisible);
                Preferences::Save();
            }
            if (ImGui::MenuItem("Settings", nullptr, isSettingsWindowVisible)) {
                isSettingsWindowVisible = !isSettingsWindowVisible;
                Preferences::SetBool("settings_window",
                                     isSettingsWindowVisible);
                Preferences::Save();
            }
            if (ImGui::MenuItem("Create new Scene")) {
                openNewSceneModal = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Application::DrawStatsWindow(const ImGuiIO& io) {
    if (isStatsWindowVisible) {
        ImGui::Begin("Stats", &isStatsWindowVisible);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }
}

void Application::DrawSettingsWindow() {
    if (isSettingsWindowVisible) {
        ImGui::Begin("Settings", &isSettingsWindowVisible);
        if (ImGui::Checkbox("Enable VSync", &isVsyncEnabled)) {
            SDL_GL_SetSwapInterval(isVsyncEnabled);
            Preferences::SetBool("vsync", isVsyncEnabled);
            Preferences::Save();
        }

        if (ImGui::Checkbox("Cap Framerate", &isFramerateCapped)) {
            Preferences::SetBool("cap_framerate", isFramerateCapped);
            Preferences::Save();
        }
        ImGui::SameLine();
        if (ImGui::DragFloat("##Framerate Cap", &framerateCap, 1.f, 1, 0,
                             "%.1f")) {
            Preferences::SetFloat("framerate_cap", framerateCap);
        }
        ImGui::End();
    }
}

void Application::DrawControlWindow() {
    // Hide the tab bar for the window by default.
    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_AutoHideTabBar;
    ImGui::SetNextWindowClass(&window_class);

    ImGui::Begin("Control");
    if (isPaused) {
        if (ImGui::Button("Play", {50, 22})) {
            isPaused = false;
        }
    } else {
        if (ImGui::Button("Pause", {50, 22})) {
            isPaused = true;
        }
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!isPaused);
    if (ImGui::Button("Step")) {
        isStepping = true;
    }
    ImGui::EndDisabled();
    ImGui::End();
}

void Application::DrawNewSceneModal() {
    if (openNewSceneModal) {
        // Need to do this here, so that the menu is not in the id stack.
        // see https://github.com/ocornut/imgui/issues/331
        ImGui::OpenPopup("New Scene");
        openNewSceneModal = false;
    }
    if (ImGui::BeginPopupModal("New Scene", NULL,
                               ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Create new scene .cpp/.h files in the src/scenes folder.");

        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        static char errorText[256] = "";
        if (strlen(errorText)) {
            ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), errorText);
        }

        static char sceneFilename[256] = "";
        ImGui::InputText("Class Name", sceneFilename, 256);
        static char displayText[256] = "";
        ImGui::InputText("Display Text", displayText, 256);

        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        if (ImGui::Button("OK", ImVec2(200, 0))) {
            if (strlen(sceneFilename) == 0) {
                strcpy(errorText, "Class Name cannot be empty.");
            } else if (strlen(displayText) == 0) {
                strcpy(errorText, "Display Text cannot be empty.");
            } else {
                if (!CreateNewScene(sceneFilename, displayText)) {
                    strcpy(errorText, "File already exists.");
                } else {
                    sceneFilename[0] = 0;
                    displayText[0] = 0;
                    ImGui::CloseCurrentPopup();
                }
            }
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

bool Application::CreateNewScene(const char* filename,
                                 const char* displayText) {
    std::string headerPath = "../src/scenes/";
    headerPath.append(filename).append(".h");
    std::string sourcePath = "../src/scenes/";
    sourcePath.append(filename).append(".cpp");

    std::ifstream headerFileRead(headerPath);
    if (headerFileRead.good()) {
        return false;
    }

    std::ofstream headerFile(headerPath);
    headerFile << "#pragma once\n\n"
               << "#include \"core/Simple2DScene.h\"\n\n"
               << "class " << filename << " : public Simple2DScene {\n"
               << "public:\n"
               << "    virtual void OnEnable() override;\n"
               << "    virtual void OnDisable() override;\n"
               << "    virtual void Update(float deltaTime) override;\n"
               << "    virtual void Draw() override;\n"
               << "    virtual void DrawGUI() override;\n\n"
               << "    virtual const char* GetName() override { return \""
               << displayText << "\"; "
               << "};\n"
               << "};\n";
    headerFile.close();

    std::ofstream sourceFile(sourcePath);
    sourceFile << "#include \"" << filename << ".h\"\n\n"
               << "#include \"imgui.h\"\n\n"
               << "void " << filename << "::OnEnable() {}\n\n"
               << "void " << filename << "::OnDisable() {}\n\n"
               << "void " << filename << "::Update(float deltaTime) {}\n\n"
               << "void " << filename << "::Draw() {}\n\n"
               << "void " << filename << "::DrawGUI() {\n"
               << "    ImGui::Begin(\"Inspector\");\n"
               << "    ImGui::End();\n"
               << "}\n";
    sourceFile.close();
    return true;
}
